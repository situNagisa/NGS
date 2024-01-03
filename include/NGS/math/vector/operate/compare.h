#pragma once

#include "../concept.h"
#include "./size.h"
#include "./access.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class _L, class _R>
	concept comparable = maybe_same_extent<_L, _R>&& ::std::equality_comparable_with<::std::ranges::range_value_t<_L>, ::std::ranges::range_value_t<_R>>;
}

constexpr bool equal(const auto& left, const auto& right)
	requires _detail::comparable<decltype(left), decltype(right)>
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
NGS_LIB_BEGIN

constexpr bool operator==(const auto& left, const auto& right)
	requires NGS_LIB_MODULE_NAME::_detail::comparable<decltype(left), decltype(right)>&& tag_vector<decltype(left)>&& tag_vector<decltype(right)>
{
	return NGS_LIB_MODULE_NAME::equal(left, right);
}

NGS_LIB_END