#pragma once

#include "NGS/ngl/vertex/vertex_array/line_vertex.h"

NGL_BEGIN
NGL_OBJ_BEGIN

NGS_HPP_INLINE LineVertexArray::LineVertexArray(buffers::Vertex** vertices, size_t count, Usage indices_usage, bool is_reference = true)
	: IndicesVertexArray(vertices, count, indices_usage, 2 * count, is_reference)
{
	NGS_ASSERT(count > 1);
}

NGS_HPP_INLINE void LineVertexArray::AddBrokenLine(const void_ptr_cst* data_ptr, size_t count)
{
	NGS_ASSERT(count > 1);
	std::vector<indices_t> indices{};
	for (size_t i = _count; i < _count + count - 1; i++)
	{
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	_indices.Write(indices.data(), indices.size(), _count);
	VertexArray::AddVertexes(data_ptr, count);
}

NGS_END
NGL_END
