#pragma once

#include "../enum.h"
#include "./point.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct triangle : basic_indices_drawer < triangle, enums::draw_mode::triangles, 2, [](::std::size_t vertex_count) { return vertex_count - 2; } >
{
	NGS_MPL_ENVIRON_BEGIN(triangle);
public:
	template<::std::integral Index>
	constexpr static decltype(auto) fragment_indices(Index index, ::std::size_t triangle_count, ::std::indirectly_writable<Index> auto out)
	{
		using index_type = type_traits::naked_t<Index>;
		for (index_type i = static_cast<index_type>(0); i < triangle_count; ++i)
		{
			out = point::vertex_indices(index, 1, out);
			out = point::vertex_indices(index + i + 1, 2,  out);
		}
		return out;
	}
	constexpr static ::std::size_t fragment_count(::std::size_t triangle_count)
	{
		return 3 * triangle_count;
	}
};

NGS_LIB_MODULE_END