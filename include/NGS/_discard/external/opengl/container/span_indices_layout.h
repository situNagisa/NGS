#pragma once

#include "./indices_layout.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<
	::std::size_t VertexSize,
	valid_fundamental IndexType,
	indices::indices_drawer<IndexType, ::std::ranges::iterator_t<::std::vector<IndexType>>> IndicesDrawer,
	contexts::vertex_buffer_descriptor... BufferDescriptor
>
	requires (VertexSize >= IndicesDrawer::at_least_vertex_count())
using span_indices_layout = indices_layout<policy::layout<policy::vertex_buffer<::std::span<BufferDescriptor, VertexSize>>...>, policy::indices_buffer<::std::span<IndexType, IndicesDrawer::indices_count_of(VertexSize)>, IndicesDrawer>>;

template<
	valid_fundamental IndexType,
	indices::indices_drawer<IndexType, ::std::ranges::iterator_t<::std::vector<IndexType>>> IndicesDrawer,
	contexts::vertex_buffer_descriptor... BufferDescriptor
>
using dynamic_span_indices_layout = indices_layout<policy::layout<policy::vertex_buffer<::std::span<BufferDescriptor>>...>, policy::indices_buffer<::std::span<IndexType>, IndicesDrawer>>;

NGS_LIB_MODULE_END