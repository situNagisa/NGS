#pragma once

#include "../enum.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T, class IndexType, class Out = IndexType*>
concept indices_drawer = ::std::indirectly_writable<Out, IndexType>&& ::std::weakly_incrementable<Out>&&
	requires(IndexType index, ::std::size_t vertex_count, Out out)
{
	{ T::draw_mode() } -> ::std::convertible_to<enums::draw_mode>;
	{ T::vertex_indices(index, vertex_count, out) } -> ::std::same_as<Out>;
	{ T::indices_count_of(vertex_count) } -> ::std::convertible_to<::std::size_t>;
	{ T::at_least_vertex_count() } -> ::std::convertible_to<::std::size_t>;
};

NGS_LIB_MODULE_END