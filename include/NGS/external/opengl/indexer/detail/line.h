#pragma once

#include "./point.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct line : basic_indices_drawer < line, enums::element_draw_mode::lines, 2, [](::std::size_t vertex_count) { return vertex_count - 2; } >
{
	NGS_PP_INJECT(line);
public:
	template<::std::integral Index>
	constexpr static decltype(auto) fragment_indices(Index index, ::std::indirectly_writable<Index> auto out)
	{
		return point::primitive_topology_auto_index(index, 2, out);
	}
	template<::std::integral Index>
	constexpr static decltype(auto) fragment_indices(Index index, ::std::size_t break_point_count, ::std::indirectly_writable<Index> auto out)
	{
		for (auto i = index; i < index + break_point_count + 1; ++i)
		{
			out = self_type::fragment_indices(i, out);
		}
		return out;
	}
	constexpr static ::std::size_t fragment_count(::std::size_t break_point_count)
	{
		return 2 * (break_point_count + 1);
	}
};

NGS_LIB_MODULE_END