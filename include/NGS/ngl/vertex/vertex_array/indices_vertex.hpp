#pragma once

#include "NGS/ngl/vertex/vertex_array/indices_vertex.h"

NGL_BEGIN
NGL_OBJ_BEGIN

NGS_HPP_INLINE IndicesVertexArray::IndicesVertexArray(buffers::Vertex** vertices, size_t count, Usage indices_usage, size_t indices_count, bool is_reference = true)
	: VertexArray(vertices, count, is_reference)
	, _indices(indices_count == default_indices_count ? (count) : (indices_count), indices_usage)
{}

NGS_HPP_INLINE inline void IndicesVertexArray::AddVertexes(const void_ptr_cst* data_ptr, size_t count)
{
	std::vector<indices_t> indices{};
	for (size_t i = _count; i < _count + count; i++)
	{
		indices.push_back(i);
	}
	_indices.Write(indices.data(), indices.size(), _count);
	VertexArray::AddVertexes(data_ptr, count);
}



NGS_END
NGL_END
