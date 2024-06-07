#pragma once

#include "../concept.h"
#include "./basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr bool static_compare(const concepts::shape auto& left, const concepts::shape auto& right)
{
	using left_type = decltype(left);
	using right_type = decltype(right);

	if constexpr (NGS_LIB_MODULE_NAME::rank<left_type>() == NGS_LIB_MODULE_NAME::rank<right_type>())
	{
		for (traits::rank_t i = 0; i < NGS_LIB_MODULE_NAME::rank<left_type>(); ++i)
		{
			if (NGS_LIB_MODULE_NAME::static_extent<left_type>(i) != NGS_LIB_MODULE_NAME::static_extent<right_type>(i))
			{
				return false;
			}
		}
	}
	return true;
}

constexpr bool compare(const concepts::shape auto& left, const concepts::shape auto& right)
{
	using left_type = decltype(left);
	using right_type = decltype(right);

	if constexpr( NGS_LIB_MODULE_NAME::rank<left_type>() == NGS_LIB_MODULE_NAME::rank<right_type>())
	{
		for (traits::rank_t i = 0; i < NGS_LIB_MODULE_NAME::rank<left_type>(); ++i)
		{
			if (NGS_LIB_MODULE_NAME::extent(left, i) != NGS_LIB_MODULE_NAME::extent(right, i))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

NGS_LIB_MODULE_END