#pragma once

#include "../reflect.h"
#include "../enum.h"
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
struct array_indices_layout : indices_layout<policy::layout<policy::vertex_buffer<::std::array<BufferDescriptor, VertexSize>>...>, policy::indices_buffer<::std::array<IndexType, IndicesDrawer::indices_count_of(VertexSize)>, IndicesDrawer>>
{
	NGS_MPL_ENVIRON2(array_indices_layout, indices_layout<policy::layout<policy::vertex_buffer<::std::array<BufferDescriptor, VertexSize>>...>, policy::indices_buffer<::std::array<IndexType, IndicesDrawer::indices_count_of(VertexSize)>, IndicesDrawer>>);

public:
	array_indices_layout(bool normalized, enums::usage vertex_usage, enums::usage indices_usage)
		: base_type(
			{ normalized, vertex_usage },
			{ indices_usage }
		)
	{}

	array_indices_layout(bool normalize, enums::usage usage)
		: self_type(normalize, usage, usage)
	{}
};

NGS_LIB_MODULE_END