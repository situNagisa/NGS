#pragma once

#include "../../basic.h"
#include "../../indexer.h"
#include "./buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class Indexer, ::std::ranges::contiguous_range Range>
	requires NGS_EXTERNAL_OPENGL_INDEXER_NS::topology_indexer<Indexer, ::std::ranges::range_value_t<Range>> && NGS_EXTERNAL_OPENGL_BASIC_REFLECT_NS::buffer_indices<::std::ranges::range_value_t<Range>>
struct indices_buffer : buffer<NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::indices_buffer, Range>
{
	NGS_PP_INJECT_EXPLICIT(indices_buffer, buffer<NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::indices_buffer, Range>);
public:
	using indexer_type = Indexer;

	using base_type::base_type;
	using base_type::operator=;

	constexpr auto auto_index(buffer_value_t<base_type> index,::std::size_t vertex_count, ::std::ranges::iterator_t<typename base_type::range_type> out)
		requires NGS_EXTERNAL_OPENGL_INDEXER_NS::topology_indexer<indexer_type, ::std::ranges::range_value_t<Range>, ::std::ranges::iterator_t<Range>>
	{
		return indexer_type::primitive_topology_auto_index(index, vertex_count, out);
	}
	constexpr decltype(auto) auto_index(buffer_value_t<base_type> index, ::std::size_t vertex_count, ::std::ranges::range_difference_t<typename base_type::range_type> offset)
		requires NGS_EXTERNAL_OPENGL_INDEXER_NS::topology_indexer<indexer_type, ::std::ranges::range_value_t<Range>, ::std::ranges::iterator_t<Range>>
	{
		return ::std::ranges::distance(self_type::auto_index(index, vertex_count, ::std::ranges::next(::std::ranges::begin(base_type::data()),offset)),::std::ranges::begin(base_type::data()));
	}
};

template<class Indexer, ::std::size_t IndexCount, NGS_EXTERNAL_OPENGL_BASIC_REFLECT_NS::buffer_indices Index>
	requires NGS_EXTERNAL_OPENGL_INDEXER_NS::topology_indexer<Indexer, Index>
decltype(auto) make_array_indices_buffer(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage usage, auto&&... array_args)
	requires ::std::constructible_from<::std::array<Index, IndexCount>, decltype(array_args)...>
{
	return indices_buffer<Indexer, ::std::array<Index, IndexCount>>(usage, { NGS_PP_PERFECT_FORWARD(array_args)... });
}

template<class Indexer, ::std::size_t IndexCount, NGS_EXTERNAL_OPENGL_BASIC_REFLECT_NS::buffer_indices Index>
	requires NGS_EXTERNAL_OPENGL_INDEXER_NS::topology_indexer<Indexer, Index>
decltype(auto) make_span_indices_buffer(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage usage, ::std::span<Index, IndexCount> data)
{
	return indices_buffer<Indexer, ::std::span<Index, IndexCount>>(usage, data);
}

template<class Indexer, NGS_EXTERNAL_OPENGL_BASIC_REFLECT_NS::buffer_indices Index>
	requires NGS_EXTERNAL_OPENGL_INDEXER_NS::topology_indexer<Indexer, Index>
decltype(auto) make_span_indices_buffer(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage usage, ::std::span<Index> data)
{
	return indices_buffer<Indexer, ::std::span<Index>>(usage, data);
}

template<class Indexer, NGS_EXTERNAL_OPENGL_BASIC_REFLECT_NS::buffer_indices Index>
	requires NGS_EXTERNAL_OPENGL_INDEXER_NS::topology_indexer<Indexer, Index>
decltype(auto) make_vector_indices_buffer(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage usage, auto&&... range_args)
	requires ::std::constructible_from<::std::vector<Index>, decltype(range_args)...>
{
	return indices_buffer<Indexer, ::std::vector<Index>>(usage, ::std::vector<Index>(NGS_PP_PERFECT_FORWARD(range_args)...));
}

NGS_LIB_MODULE_END

