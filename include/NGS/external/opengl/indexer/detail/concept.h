#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T, class IndexType, class Out = type_traits::naked_t<IndexType>*>
concept topology_indexer = ::std::indirectly_writable<Out, IndexType>&& ::std::weakly_incrementable<Out>&&
	requires(IndexType index, ::std::size_t vertex_count, Out out)
{
	{ T::topology() } -> ::std::convertible_to<enums::element_draw_mode>;
	{ T::primitive_topology_auto_index(index, vertex_count, out) } -> ::std::same_as<Out>;
	{ T::indices_count_of(vertex_count) } -> ::std::convertible_to<::std::size_t>;
	{ T::at_least_vertex_count() } -> ::std::convertible_to<::std::size_t>;
};

NGS_LIB_MODULE_END