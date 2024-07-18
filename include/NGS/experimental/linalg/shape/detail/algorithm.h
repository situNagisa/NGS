#pragma once

#include "./rank.h"
#include "./shape.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<shape T>
constexpr auto index_cast(::std::integral auto&& index) noexcept
{
	if constexpr(!::std::same_as<bool, ::std::remove_cvref_t<decltype(index)>>)
	{
		return index;
	}
	else
	{
		return static_cast<shape_index_t<T>>(index);
	}
}

constexpr decltype(auto) operator==(shape auto&& left, shape auto&& right)
{
	using left_type = ::std::remove_reference_t<decltype(left)>;
	using right_type = ::std::remove_reference_t<decltype(right)>;

	if constexpr (NGS_LIB_MODULE_NAME::rank(shape_ranks_v<left_type>) != NGS_LIB_MODULE_NAME::rank(shape_ranks_v<right_type>))
	{
		return false;
	}
	else if constexpr (!::std::ranges::equal(shape_ranks_v<left_type>, shape_ranks_v<right_type>))
	{
		return false;
	}
	else
	{
		for (rank_t i = 0; i < NGS_LIB_MODULE_NAME::rank<left_type>(); ++i)
		{
			if (extent_at(NGS_PP_PERFECT_FORWARD(left), i) != extent_at(NGS_PP_PERFECT_FORWARD(right), i))
			{
				return false;
			}
		}
		return true;
	}
}

NGS_LIB_MODULE_END