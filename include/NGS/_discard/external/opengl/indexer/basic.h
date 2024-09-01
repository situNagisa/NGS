#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN
	template<class Derived, NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::element_draw_mode DrawMode, ::std::size_t LeastVertexCount,::std::invocable<::std::size_t> auto Map>
	requires requires(::std::size_t vertex_count) { { Map(vertex_count) } -> ::std::convertible_to<::std::size_t>; }
struct basic_indices_drawer
{
	NGS_PP_INJECT_BEGIN(basic_indices_drawer);
public:
	using derived_type = Derived;

	constexpr static NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::element_draw_mode topology() { return DrawMode; }
	constexpr static ::std::size_t at_least_vertex_count() { return LeastVertexCount; }
	constexpr static ::std::size_t map(::std::size_t vertex_count)
	{
		if (!::std::is_constant_evaluated())
		{
			NGS_ASSERT(vertex_count >= at_least_vertex_count());
		}
		return Map(vertex_count);
	}
	template<::std::integral Index>
	constexpr static decltype(auto) primitive_topology_auto_index(Index index, ::std::size_t vertex_count, ::std::indirectly_writable<Index> auto out)
	{
		return derived_type::fragment_indices(index, self_type::map(vertex_count), out);
	}

	constexpr static ::std::size_t indices_count_of(::std::size_t vertex_count)
	{
		return derived_type::fragment_count(self_type::map(vertex_count));
	}
};

NGS_LIB_MODULE_END