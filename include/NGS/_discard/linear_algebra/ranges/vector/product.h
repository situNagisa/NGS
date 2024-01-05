#pragma once

#include "./defined.h"

NGS_MATH_LA_VECTOR_CONCEPT_BEGIN

template<class _L, class _R = _L>
concept inner_productable = expression<_L> && expression<_R> && same_type<_L, _R>&&
	requires(traits::vectors::value_t<_L> l, traits::vectors::value_t<_R> r) { (l * r) + (l * r); };

template<class _L, class _R = _L>
concept outer_productable = expression<_L> && expression<_R> && same_type<_L, _R>&& adapters::vectors::dimension_equality<_L, 3>&&
cpt::multipliable<traits::vectors::value_t<_L>, traits::vectors::value_t<_R>>;

NGS_MATH_LA_VECTOR_CONCEPT_END

NGS_MATH_LA_VECTOR_TRAIT_BEGIN
template<class _L, class _R = _L>
	requires concepts::vectors::inner_productable<_L, _R>
using inner_product_t = type_traits::add_t<type_traits::multiply_t<value_t<_L>, value_t<_R>>>;

NGS_MATH_LA_VECTOR_TRAIT_END
NGS_MATH_LA_VECTOR_RANGE_BEGIN

template<class _L, class _R>
	requires concepts::vectors::inner_productable<_L, _R>
constexpr decltype(auto) product_inner(_L&& left, _R&& right)
{
	using value_type = type_traits::add_t<type_traits::multiply_t<traits::vectors::value_t<_L>, traits::vectors::value_t<_R>>>;
	value_type result{};
	for (size_t i = 0; i < adapters::vectors::dimension(left); i++)
	{
		result += adapters::vectors::access(NGS_PP_PERFECT_FORWARD(left), i) * adapters::vectors::access(NGS_PP_PERFECT_FORWARD(right), i);
	}
	return result;
}

template<class _L, class _R>
	requires concepts::vectors::outer_productable<_L, _R>
constexpr decltype(auto) product_outer(_L&& left, _R&& right)
{
	using value_type = type_traits::multiply_t<traits::vectors::value_t<_L>, traits::vectors::value_t<_R>>;
	using result_type = containers::vectors::vector3<value_type>;

	if constexpr (!yap::complexity<_L> && !yap::complexity<_R>)
	{
		return result_type
		(
			adapters::vectors::access(NGS_PP_PERFECT_FORWARD(left), 1) * adapters::vectors::access(NGS_PP_PERFECT_FORWARD(right), 2) - adapters::vectors::access(NGS_PP_PERFECT_FORWARD(left), 2) * adapters::vectors::access(NGS_PP_PERFECT_FORWARD(right), 1),
			adapters::vectors::access(NGS_PP_PERFECT_FORWARD(left), 2) * adapters::vectors::access(NGS_PP_PERFECT_FORWARD(right), 0) - adapters::vectors::access(NGS_PP_PERFECT_FORWARD(left), 0) * adapters::vectors::access(NGS_PP_PERFECT_FORWARD(right), 2),
			adapters::vectors::access(NGS_PP_PERFECT_FORWARD(left), 0) * adapters::vectors::access(NGS_PP_PERFECT_FORWARD(right), 1) - adapters::vectors::access(NGS_PP_PERFECT_FORWARD(left), 1) * adapters::vectors::access(NGS_PP_PERFECT_FORWARD(right), 0)
		);
	}
	else if constexpr (yap::complexity<_L>)
	{
		return vectors::product_outer(result_type(NGS_PP_PERFECT_FORWARD(left)), NGS_PP_PERFECT_FORWARD(right));
	}
	else if constexpr (yap::complexity<_R>)
	{
		return vectors::product_outer(NGS_PP_PERFECT_FORWARD(left), result_type(NGS_PP_PERFECT_FORWARD(left)));
	}
	else
	{
		return vectors::product_outer(result_type(NGS_PP_PERFECT_FORWARD(left)), result_type(NGS_PP_PERFECT_FORWARD(right)));
	}
}

constexpr decltype(auto) operator^(concepts::vectors::expression auto&& left, concepts::vectors::expression auto&& right)
	requires concepts::vectors::outer_productable<decltype(left), decltype(right)>
{
	return vectors::product_outer(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_MATH_LA_VECTOR_RANGE_END
NGS_MATH_LA_VECTOR_CONTAINER_BEGIN
using ranges::vectors::operator^;
NGS_MATH_LA_VECTOR_CONTAINER_END