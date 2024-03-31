#pragma once

#include "../fusion.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class Indexer>
decltype(auto) copy(::std::ranges::sized_range auto&& vertex_range, auto begin_index, auto vertex_out,auto indices_out)
	requires ::std::indirectly_copyable<::std::ranges::iterator_t<decltype(vertex_range)>, decltype(vertex_out)>
	&& ::std::indirectly_writable<decltype(indices_out), decltype(begin_index)>
	&& fusion::topology_indexer<Indexer,decltype(begin_index), decltype(indices_out)>
{
	auto indices_result = Indexer::primitive_topology_auto_index(begin_index, ::std::ranges::size(NGS_PP_PERFECT_FORWARD(vertex_range)), indices_out);
	auto vertex_result = ::std::ranges::copy(NGS_PP_PERFECT_FORWARD(vertex_range), vertex_out).out;

	return ::std::pair{ vertex_result, indices_result };
}

NGS_LIB_MODULE_END