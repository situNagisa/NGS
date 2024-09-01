#pragma once

#include "../operator.h"
#include "../concept.h"
#include "./size.h"
#include "./access.h"
#include "./defined.h"


NGS_LIB_BEGIN
namespace NGS_MATH_VECTOR_CPT_NS
{
	namespace _detail_compare
	{
		template<class _L, class _R>
		concept equality_comparable = requires(::std::ranges::range_value_t<_L> l, ::std::ranges::range_value_t<_R> r)
		{
			l == r;
			l != r;
		};

	}
	template<class _L, class _R>
	concept equality_comparable_with =
		accessable_vector<_L> && accessable_vector<_R> &&
		input_vector<_L > && input_vector<_R> &&
		maybe_same_extent<_L, _R>&& _detail_compare::equality_comparable<_L, _R>;
}
NGS_LIB_END
NGS_LIB_MODULE_BEGIN

constexpr bool equal(const auto& left, const auto& right)
	requires equality_comparable_with<decltype(left), decltype(right)>
{
	NGS_MATH_VECTOR_CHECK_SIZE(left, right);
	extent_t extent = NGS_LIB_MODULE_NAME::size(left, right);
	for (index_t i = 0; i < extent; ++i)
	{
		if (NGS_MATH_VECTOR_OPERATE_NS::access(left, i) != NGS_MATH_VECTOR_OPERATE_NS::access(right, i))
		{
			return false;
		}
	}
	return true;
}

NGS_LIB_MODULE_END
NGS_MATH_VECTOR_OPERATOR_BEGIN

constexpr bool operator==(const operator_vector auto& left, const operator_vector auto& right)
	requires equality_comparable_with<decltype(left), decltype(right)>
{
	return NGS_LIB_MODULE_NAME::equal(left, right);
}

NGS_MATH_VECTOR_OPERATOR_END