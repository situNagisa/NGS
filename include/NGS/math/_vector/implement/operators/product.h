#pragma once

#include "NGS/math/vector/concept.h"
#include "../standard.h"

NGS_MATH_VECTOR_FUNCTOR_BEGIN

template<class _L, class _R = _L>
concept inner_productable =
expression<_L> &&
expression<_R> &&
dimension_equality<_L, _R>&&
	requires(value_t<_L> l, value_t<_R> r) { (l * r) + (l * r); };

template<class _L, class _R = _L>
	requires inner_productable<_L, _R>
using inner_product_t = type_traits::add_t<type_traits::multiply_t<value_t<_L>, value_t<_R>>>;

template<class _L, class _R = _L>
concept outer_productable = expression<_L> && expression<_R> && dimension_equality<_L, _R>&& dimension_is<_L, 3>&& cpt::multipliable<value_t<_L>, value_t<_R>>;

NGS_MATH_VECTOR_FUNCTOR_END

NGS_MATH_VECTOR_BEGIN

template<class _L, class _R>
	requires functor::inner_productable<_L, _R>
constexpr decltype(auto) product_inner(_L&& left, _R&& right)
{
	using value_type = type_traits::add_t<type_traits::multiply_t<functor::value_t<_L>, functor::value_t<_R>>>;
	value_type result{};
	for (size_t i = 0; i < functor::dimension<_L>; i++)
	{
		result += functor::access(NGS_PP_PERFECT_FORWARD(left), i) * functor::access(NGS_PP_PERFECT_FORWARD(right), i);
	}
	return result;
}

template<class _L, class _R>
	requires functor::outer_productable<_L, _R>
constexpr decltype(auto) product_outer(_L&& left, _R&& right)
{
	using value_type = type_traits::multiply_t<functor::value_t<_L>, functor::value_t<_R>>;
	using result_type = vector<3, value_type>;

	if constexpr (!yap::complexity<_L> && !yap::complexity<_R>)
	{
		return result_type
		(
			functor::access(NGS_PP_PERFECT_FORWARD(left), 1) * functor::access(NGS_PP_PERFECT_FORWARD(right), 2) - functor::access(NGS_PP_PERFECT_FORWARD(left), 2) * functor::access(NGS_PP_PERFECT_FORWARD(right), 1),
			functor::access(NGS_PP_PERFECT_FORWARD(left), 2) * functor::access(NGS_PP_PERFECT_FORWARD(right), 0) - functor::access(NGS_PP_PERFECT_FORWARD(left), 0) * functor::access(NGS_PP_PERFECT_FORWARD(right), 2),
			functor::access(NGS_PP_PERFECT_FORWARD(left), 0) * functor::access(NGS_PP_PERFECT_FORWARD(right), 1) - functor::access(NGS_PP_PERFECT_FORWARD(left), 1) * functor::access(NGS_PP_PERFECT_FORWARD(right), 0)
		);
	}
	else if constexpr (yap::complexity<_L>)
	{
		return product_outer(result_type(NGS_PP_PERFECT_FORWARD(left)), NGS_PP_PERFECT_FORWARD(right));
	}
	else if constexpr (yap::complexity<_R>)
	{
		return product_outer(NGS_PP_PERFECT_FORWARD(left), result_type(NGS_PP_PERFECT_FORWARD(left)));
	}
	else
	{
		return product_outer(result_type(NGS_PP_PERFECT_FORWARD(left)), result_type(NGS_PP_PERFECT_FORWARD(right)));
	}
}

constexpr decltype(auto) operator^(auto&& left, auto&& right)
	requires requires{ product_outer(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)); }
{
	return product_outer(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_MATH_VECTOR_END