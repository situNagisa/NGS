#pragma once

#include "../basic.h"
#include "../buffer.h"
#include "../algorithm.h"
#include "./auto.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<cpt::derived_from_specialization<NGS_EXTERNAL_OPENGL_BUFFER_NS::vertex_group> VertexGroup, cpt::derived_from_specialization<NGS_EXTERNAL_OPENGL_BUFFER_NS::indices_buffer> IndexBuffer>
struct index_manager : auto_manager<VertexGroup>
{
	NGS_MPL_ENVIRON2(index_manager, auto_manager<VertexGroup>);
public:
	using index_buffer_type = IndexBuffer;

	index_manager(typename base_type::group_type&& group, index_buffer_type&& index,bool normalized = false)
		: base_type(::std::move(group),normalized)
		, _index(::std::move(index))
	{}

	auto&& index() { return _index; }
	auto&& index() const { return _index; }

	void describe(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage vertex_usage, NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage indices_usage)
	{
		base_type::group().describe(vertex_usage);
		NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::bind(_index.get_context());
		_index.describe(indices_usage);
	}

	void submit()
	{
		base_type::group().submit();
		NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::bind(_index.get_context());
		_index.submit();
	}

	void draw(::std::ranges::range_difference_t<NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_range_t<index_buffer_type>> offset, ::std::ranges::range_size_t<NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_range_t<index_buffer_type>> count)
	{
		NGS_ASSERT(static_cast<::std::ranges::range_size_t<NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_range_t<index_buffer_type>>>(offset + count) <= ::std::ranges::size(_index.data()), "out of range");
		base_type::array().get_context().draw_elements(index_buffer_type::indexer_type::topology(), count, NGS_EXTERNAL_OPENGL_BASIC_REFLECT_NS::buffer_indices_reflecter::reflect<NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_value_t<index_buffer_type>>::value, offset);
	}
	void draw() { self_type::draw(0, ::std::ranges::size(_index.data())); }

	decltype(auto) copy_from(
		::std::ranges::sized_range auto&& vertex_range,
		NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_value_t<index_buffer_type> begin_index,
		::std::ranges::iterator_t<typename base_type::group_type> vertex_out,
		::std::ranges::iterator_t<NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_range_t<index_buffer_type>> indices_out
	)
	{
		return NGS_EXTERNAL_OPENGL_ALGORITHM_NS::copy<typename index_buffer_type::indexer_type>(NGS_PP_PERFECT_FORWARD(vertex_range), begin_index, vertex_out, indices_out);
	}
	decltype(auto) copy_from(
		::std::ranges::sized_range auto&& vertex_range,
		NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_value_t<index_buffer_type> begin_index,
		::std::ranges::range_difference_t<typename base_type::group_type> vertex_out,
		::std::ranges::range_difference_t<NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_range_t<index_buffer_type>> indices_out
	)
	{
		return self_type::copy_from(NGS_PP_PERFECT_FORWARD(vertex_range), begin_index, ::std::ranges::next(::std::ranges::begin(base_type::group()), vertex_out), ::std::ranges::next(::std::ranges::begin(_index.data()), indices_out));
	}

	decltype(auto) copy_from(
		const ::std::initializer_list<typename base_type::vertex_type>& vertex_range,
		NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_value_t<index_buffer_type> begin_index,
		::std::ranges::iterator_t<typename base_type::group_type> vertex_out,
		::std::ranges::iterator_t<NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_range_t<index_buffer_type>> indices_out
	)
	{
		return NGS_EXTERNAL_OPENGL_ALGORITHM_NS::copy<typename index_buffer_type::indexer_type>(vertex_range, begin_index, vertex_out, indices_out);
	}
	decltype(auto) copy_from(
		const ::std::initializer_list<typename base_type::vertex_type>& vertex_range,
		NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_value_t<index_buffer_type> begin_index,
		::std::ranges::range_difference_t<typename base_type::group_type> vertex_out,
		::std::ranges::range_difference_t<NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_range_t<index_buffer_type>> indices_out
	)
	{
		return self_type::copy_from(vertex_range, begin_index, ::std::ranges::next(::std::ranges::begin(base_type::group()),vertex_out), ::std::ranges::next(::std::ranges::begin(_index.data()),indices_out));
	}

	index_buffer_type _index;
};

template<cpt::derived_from_specialization<NGS_EXTERNAL_OPENGL_BUFFER_NS::vertex_group> VertexGroup, cpt::derived_from_specialization<NGS_EXTERNAL_OPENGL_BUFFER_NS::indices_buffer> IndexBuffer>
index_manager(VertexGroup&&, IndexBuffer&&, bool) -> index_manager<VertexGroup, IndexBuffer>;

template<cpt::derived_from_specialization<NGS_EXTERNAL_OPENGL_BUFFER_NS::vertex_group> VertexGroup, cpt::derived_from_specialization<NGS_EXTERNAL_OPENGL_BUFFER_NS::indices_buffer> IndexBuffer>
index_manager(VertexGroup&&, IndexBuffer&&) -> index_manager<VertexGroup, IndexBuffer>;

template<
	class Indexer,
	::std::size_t VertexCount,
	NGS_EXTERNAL_OPENGL_BASIC_REFLECT_NS::buffer_indices Index,
	NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_descriptor... Buffers
> requires NGS_EXTERNAL_OPENGL_INDEXER_NS::topology_indexer<Indexer, Index>
decltype(auto) make_array_index_manager(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage vertex, NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage indices, bool normalized = false)
{
	return index_manager{ NGS_EXTERNAL_OPENGL_BUFFER_NS::make_array_vertex_group<VertexCount,Buffers...>(vertex), NGS_EXTERNAL_OPENGL_BUFFER_NS::make_array_indices_buffer<Indexer, Indexer::indices_count_of(VertexCount), Index>(indices), normalized};
}

template<
	class Indexer,
	::std::size_t VertexCount,
	NGS_EXTERNAL_OPENGL_BASIC_REFLECT_NS::buffer_indices Index,
	NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_descriptor... Buffers
> requires NGS_EXTERNAL_OPENGL_INDEXER_NS::topology_indexer<Indexer, Index>
decltype(auto) make_array_index_manager(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage usage, bool normalized = false)
{
	return NGS_LIB_MODULE_NAME::make_array_index_manager<Indexer, VertexCount, Index, Buffers...>(usage, usage, normalized);
}

template<
	class Indexer,
	::std::size_t VertexCount,
	NGS_EXTERNAL_OPENGL_BASIC_REFLECT_NS::buffer_indices Index,
	NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_descriptor... Buffers
> requires NGS_EXTERNAL_OPENGL_INDEXER_NS::topology_indexer<Indexer, Index>
decltype(auto) make_span_index_manager(
	NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage vertex, 
	NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage indices, 
	bool normalized, 
	::std::span<Index, Indexer::indices_count_of(VertexCount)> indices_data,
	::std::span<Buffers, VertexCount>... vertex_data
)
{
	return index_manager{
		NGS_EXTERNAL_OPENGL_BUFFER_NS::make_span_vertex_group(vertex,vertex_data...),
		NGS_EXTERNAL_OPENGL_BUFFER_NS::make_span_indices_buffer<Indexer>(indices,indices_data),
		normalized
	};
}

template<
	class Indexer,
	NGS_EXTERNAL_OPENGL_BASIC_REFLECT_NS::buffer_indices Index,
	NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_descriptor... Buffers
> requires NGS_EXTERNAL_OPENGL_INDEXER_NS::topology_indexer<Indexer, Index>
decltype(auto) make_span_index_manager(
	NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage vertex,
	NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage indices,
	bool normalized,
	::std::span<Index> indices_data,
	::std::span<Buffers>... vertex_data
)
{
	return index_manager{
		NGS_EXTERNAL_OPENGL_BUFFER_NS::make_span_vertex_group(vertex,vertex_data...),
		NGS_EXTERNAL_OPENGL_BUFFER_NS::make_span_indices_buffer<Indexer>(indices,indices_data),
		normalized
	};
}

template<
	class Indexer,
	::std::size_t VertexCount,
	NGS_EXTERNAL_OPENGL_BASIC_REFLECT_NS::buffer_indices Index,
	NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_descriptor... Buffers
> requires NGS_EXTERNAL_OPENGL_INDEXER_NS::topology_indexer<Indexer, Index>
decltype(auto) make_span_index_manager(
	NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage vertex,
	NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage indices,
	bool normalized,
	::std::span<Index, Indexer::indices_count_of(VertexCount)> indices_data,
	type_traits::add_cv_like_t<Buffers, void>*... vertex_data
)
{
	return index_manager{
		NGS_EXTERNAL_OPENGL_BUFFER_NS::make_span_vertex_group<VertexCount, Buffers...>(vertex,vertex_data...),
		NGS_EXTERNAL_OPENGL_BUFFER_NS::make_span_indices_buffer<Indexer>(indices,indices_data),
		normalized
	};
}

template<
	class Indexer,
	NGS_EXTERNAL_OPENGL_BASIC_REFLECT_NS::buffer_indices Index,
	NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_descriptor... Buffers
> requires NGS_EXTERNAL_OPENGL_INDEXER_NS::topology_indexer<Indexer, Index>
decltype(auto) make_span_index_manager(
	NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage vertex,
	NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage indices,
	bool normalized,
	::std::span<Index> indices_data,
	::std::size_t vertex_count,
	type_traits::add_cv_like_t<Buffers, void>*... vertex_data
)
{
	return index_manager{
		NGS_EXTERNAL_OPENGL_BUFFER_NS::make_span_vertex_group<Buffers...>(vertex,vertex_count, vertex_data...),
		NGS_EXTERNAL_OPENGL_BUFFER_NS::make_span_indices_buffer<Indexer>(indices,indices_data),
		normalized
	};
}


NGS_LIB_MODULE_END