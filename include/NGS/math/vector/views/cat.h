#pragma once

#include "./transform.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	inline constexpr struct
	{
		constexpr decltype(auto) operator()(index_t index, auto&& first, auto&& second)const
		{
			constexpr auto vector_extent = extent_v<decltype(first)>;
			if (index < vector_extent)
				return NGS_MATH_VECTOR_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(first), index);
			return NGS_MATH_VECTOR_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(second), index - vector_extent);
		}
	}cat_transformer{};
}

template<static_extent_vector _First, static_extent_vector _Second>
using cat_view = transform_default_sentinel_view<_detail::cat_transformer, extent_v<_First> +extent_v<_Second>, _First, _Second>;

constexpr auto cat(static_extent_vector auto&& first, static_extent_vector auto&& second)
{
	return cat_view<decltype(first), decltype(second)>(NGS_PP_PERFECT_FORWARD(first), NGS_PP_PERFECT_FORWARD(second));
}

NGS_LIB_MODULE_END