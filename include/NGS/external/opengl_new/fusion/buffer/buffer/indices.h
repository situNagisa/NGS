#pragma once

#include "../../../reflect.h"
#include "../../../context.h"
#include "../topology_indexer.h"
#include "./buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::ranges::contiguous_range Range, topology_indexer<::std::ranges::range_value_t<Range>,::std::ranges::iterator_t<Range>> Indexer>
	requires reflects::buffer_indices<::std::ranges::range_value_t<Range>>
struct indices_buffer : buffer<contexts::indices_buffer, Range>
{
	NGS_MPL_ENVIRON2(indices_buffer, buffer<contexts::indices_buffer, Range>);
public:
	using indexer_type = Indexer;

	using base_type::base_type;
	using base_type::operator=;

	constexpr auto auto_index(buffer_value_t<base_type> index,::std::size_t vertex_count, ::std::ranges::iterator_t<typename base_type::range_type> out)
	{
		return indexer_type::primitive_topology_auto_index(index, vertex_count, out);
	}
	constexpr decltype(auto) auto_index(buffer_value_t<base_type> index, ::std::size_t vertex_count, ::std::ranges::range_difference_t<typename base_type::range_type> offset)
	{
		return ::std::ranges::distance(self_type::auto_index(index, vertex_count, ::std::ranges::next(::std::ranges::begin(base_type::data()),offset)),::std::ranges::begin(base_type::data()));
	}
};



NGS_LIB_MODULE_END

