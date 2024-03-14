#pragma once

#include "../enum.h"
#include "./basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct point : basic_indices_drawer < point, enums::draw_mode::points, 0, [](::std::size_t vertex_count) { return vertex_count; }>
{
	NGS_MPL_ENVIRON(point);
public:
	template<::std::integral Index>
	constexpr static decltype(auto) fragment_indices(Index index, ::std::indirectly_writable<Index> auto out)
	{
		*out = index;
		return ::std::ranges::next(out);
	}
	template<::std::integral Index>
	constexpr static decltype(auto) fragment_indices(Index index, ::std::size_t vertex_count, ::std::indirectly_writable<Index> auto out)
	{
		using index_type = type_traits::naked_t<Index>;
		for (index_type i = 0; i < vertex_count; ++i)
		{
			out = self_type::fragment_indices(index + i, out);
		}
		return out;
	}

	constexpr static ::std::size_t fragment_count(::std::size_t vertex_count)
	{
		return vertex_count;
	}
};

NGS_LIB_MODULE_END