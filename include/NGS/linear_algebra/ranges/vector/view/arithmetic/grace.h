#pragma once

#include "../binary.h"

NGS_MATH_LA_VECTOR_CONCEPT_BEGIN

template<class _Left, class _Right>
concept arithmetic_operatable_with = expression<_Left> && expression<_Right> && same_type<_Left, _Right>;

template<class _Left, class _Right>
concept addable = arithmetic_operatable_with<_Left, _Right>&& cpt::addable<traits::vectors::value_t<_Left>, traits::vectors::value_t<_Right>>;

template<class _Left, class _Right>
concept subtractable = arithmetic_operatable_with<_Left, _Right>&& cpt::subtractable<traits::vectors::value_t<_Left>, traits::vectors::value_t<_Right>>;

template<class _Left, class _Right>
concept multipliable = arithmetic_operatable_with<_Left, _Right>&& cpt::multipliable<traits::vectors::value_t<_Left>, traits::vectors::value_t<_Right>>;

template<class _Left, class _Right>
concept divisible = arithmetic_operatable_with<_Left, _Right>&& cpt::divisible<traits::vectors::value_t<_Left>, traits::vectors::value_t<_Right>>;

NGS_MATH_LA_VECTOR_CONCEPT_END
NGS_MATH_LA_VECTOR_VIEW_BEGIN
namespace detail
{
	template<auto _Accessor, concepts::vectors::expression _Left, concepts::vectors::expression _Right>
		requires concepts::vectors::same_type<_Left, _Right>
	using arithmetic_functor = binary<_Accessor, ccpt::uint_<adapters::vectors::static_dimension<_Left>>, _Left, _Right>;

	inline constexpr auto add = [](auto&& left, auto&& right, traits::vectors::index_t index)
		{
			return adapters::vectors::access(NGS_PP_PERFECT_FORWARD(left), index) + adapters::vectors::access(NGS_PP_PERFECT_FORWARD(right), index);
		};
	inline constexpr auto subtract = [](auto&& left, auto&& right, traits::vectors::index_t index)
		{
			return adapters::vectors::access(NGS_PP_PERFECT_FORWARD(left), index) - adapters::vectors::access(NGS_PP_PERFECT_FORWARD(right), index);
		};
	inline constexpr auto multiply = [](auto&& left, auto&& right, traits::vectors::index_t index)
		{
			return adapters::vectors::access(NGS_PP_PERFECT_FORWARD(left), index) * adapters::vectors::access(NGS_PP_PERFECT_FORWARD(right), index);
		};
	inline constexpr auto divide = [](auto&& left, auto&& right, traits::vectors::index_t index)
		{
			return adapters::vectors::access(NGS_PP_PERFECT_FORWARD(left), index) / adapters::vectors::access(NGS_PP_PERFECT_FORWARD(right), index);
		};
}

constexpr decltype(auto) add(auto&& left, auto&& right)
	requires concepts::vectors::addable<decltype(left), decltype(right)>
{
	return detail::arithmetic_functor<detail::add, decltype(left), decltype(right) >(
		NGS_PP_PERFECT_FORWARD(left),
		NGS_PP_PERFECT_FORWARD(right)
	);
}

constexpr decltype(auto) subtract(auto&& left, auto&& right)
	requires concepts::vectors::subtractable<decltype(left), decltype(right)>
{
	return detail::arithmetic_functor<detail::subtract, decltype(left), decltype(right) >(
		NGS_PP_PERFECT_FORWARD(left),
		NGS_PP_PERFECT_FORWARD(right)
	);
}

constexpr decltype(auto) multiply(auto&& left, auto&& right)
	requires concepts::vectors::multipliable<decltype(left), decltype(right)>
{
	return detail::arithmetic_functor<detail::multiply, decltype(left), decltype(right) >(
		NGS_PP_PERFECT_FORWARD(left),
		NGS_PP_PERFECT_FORWARD(right)
	);
}

constexpr decltype(auto) divide(auto&& left, auto&& right)
	requires concepts::vectors::divisible<decltype(left), decltype(right)>
{
	return detail::arithmetic_functor<detail::divide, decltype(left), decltype(right) >(
		NGS_PP_PERFECT_FORWARD(left),
		NGS_PP_PERFECT_FORWARD(right)
	);
}


NGS_MATH_LA_VECTOR_VIEW_END