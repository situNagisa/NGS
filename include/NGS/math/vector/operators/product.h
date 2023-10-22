#pragma once

#include "../expression.h"
#include "../standard.h"

NGS_MATH_VECTOR_FUNCTOR_BEGIN

template<class _L,class _R = _L>
concept inner_productable = 
	expression<_L> && 
	expression<_R> && 
	dimension_equality<_L,_R> && 
	requires(vector_value_t<_L> l, vector_value_t<_R> r) { (l * r) + (l * r); };

template<class _L,class _R = _L>
	requires inner_productable<_L,_R>
using inner_product_t = type_traits::add_t<type_traits::multiply_t<vector_value_t<_L>,vector_value_t<_R>>>;

template<class _L,class _R = _L>
concept outer_productable = expression<_L> && expression<_R> && dimension_equality<_L,_R> && dimension_is<_L,3> && cpt::multipliable<vector_value_t<_L>,vector_value_t<_R>>;

NGS_MATH_VECTOR_FUNCTOR_END

NGS_MATH_VECTOR_BEGIN

template<class _L,class _R>
	requires functor::inner_productable<_L,_R>
constexpr decltype(auto) product_inner(_L&& left,_R&& right)
{
	using value_type = type_traits::add_t<type_traits::multiply_t<functor::vector_value_t<_L>,functor::vector_value_t<_R>>>;
	value_type result{};
	for (size_t i = 0; i < functor::dimension<_L>; i++)
	{
		result += functor::access(NGS_PERFECT_FORWARD(left), i) * functor::access(NGS_PERFECT_FORWARD(right), i);
	}
	return result;
}

template<class _L, class _R>
	requires functor::outer_productable<_L, _R>
constexpr decltype(auto) product_outer(_L&& left,_R&& right)
{
	using value_type = type_traits::multiply_t<functor::vector_value_t<_L>, functor::vector_value_t<_R>>;
	using result_type = vector<3, value_type>;

	if constexpr (!yap::complexity<_L> && !yap::complexity<_R>)
	{
		return result_type
		(
			functor::access(NGS_PERFECT_FORWARD(left), 1) * functor::access(NGS_PERFECT_FORWARD(right), 2) - functor::access(NGS_PERFECT_FORWARD(left), 2) * functor::access(NGS_PERFECT_FORWARD(right), 1),
			functor::access(NGS_PERFECT_FORWARD(left), 2) * functor::access(NGS_PERFECT_FORWARD(right), 0) - functor::access(NGS_PERFECT_FORWARD(left), 0) * functor::access(NGS_PERFECT_FORWARD(right), 2),
			functor::access(NGS_PERFECT_FORWARD(left), 0) * functor::access(NGS_PERFECT_FORWARD(right), 1) - functor::access(NGS_PERFECT_FORWARD(left), 1) * functor::access(NGS_PERFECT_FORWARD(right), 0)
		);
	}
	else if constexpr (yap::complexity<_L>)
	{
		return product_outer(result_type(NGS_PERFECT_FORWARD(left)), NGS_PERFECT_FORWARD(right));
	}
	else if constexpr (yap::complexity<_R>)
	{
		return product_outer(NGS_PERFECT_FORWARD(left), result_type(NGS_PERFECT_FORWARD(left)));
	}
	else
	{
		return product_outer(result_type(NGS_PERFECT_FORWARD(left)), result_type(NGS_PERFECT_FORWARD(right)));
	}
}

constexpr decltype(auto) operator^(auto&& left,auto&& right)
	requires requires{ product_outer(NGS_PERFECT_FORWARD(left), NGS_PERFECT_FORWARD(right)); }
{
	return product_outer(NGS_PERFECT_FORWARD(left), NGS_PERFECT_FORWARD(right));
}

NGS_MATH_VECTOR_END