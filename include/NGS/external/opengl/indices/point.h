#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

inline constexpr struct
{
	template<::std::integral Index>
	constexpr decltype(auto) operator()(Index index, ::std::indirectly_writable<Index> auto out) const
	{
		*out = index;
	}
	template<::std::integral Index>
	constexpr decltype(auto) operator()(Index index, ::std::size_t vertex_count, ::std::indirectly_writable<Index> auto out) const
	{
		using index_type = type_traits::naked_t<Index>;
		for(index_type i = 0; i < vertex_count; ++i)
		{
			(*this)(index + i, out);
		}
	}
	constexpr decltype(auto) operator()(::std::size_t vertex_count)const
	{
		return vertex_count;
	}
}add_point{};


NGS_LIB_MODULE_END