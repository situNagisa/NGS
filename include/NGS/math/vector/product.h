#pragma once

#include "./concept.h"
#include "./access.h"

NGS_LIB_BEGIN

namespace NGS_MATH_VECTOR_CPT_NS
{
	template<class _L, class _R>
	concept inner_productable = input_vector<_L> && input_vector<_R> && maybe_same_extent<_L, _R>&&
		requires(::std::ranges::range_value_t<_L> left, ::std::ranges::range_value_t<_R> right)
	{
		(left * right) + (left * right);
	};
}

template<class _L, class _R> requires inner_productable<_L, _R>
constexpr auto product_inner(_L&& left, _R right)
{
	NGS_MATH_VECTOR_CHECK_SIZE(left, right);

	using left_value_t = ::std::ranges::range_value_t<_L>;
	using right_value_t = ::std::ranges::range_value_t<_R>;
	using result_t = decltype((left_value_t{} *right_value_t{}) + (left_value_t{} *right_value_t{}));

	const auto size = ::std::ranges::size(left);
	result_t result = static_cast<result_t>(0);

	for (index_t i = 0; i < size; ++i)
	{
		result += NGS_LIB_NAME::random_access(NGS_PP_PERFECT_FORWARD(left), i) * NGS_LIB_NAME::random_access(NGS_PP_PERFECT_FORWARD(right), i);
	}

	return result;
}

NGS_LIB_END