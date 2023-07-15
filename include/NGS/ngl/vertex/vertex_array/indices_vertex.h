#pragma once

#include "NGS/ngl/vertex/vertex_array.h"
#include "NGS/ngl/vertex/indices.h"

NGL_BEGIN
NGL_OBJ_BEGIN

class IndicesVertexArray : public VertexArray {
public:
	constexpr static size_t default_indices_count = size_t(-1);

	IndicesVertexArray(IndicesVertexArray&&) = default;
	IndicesVertexArray(buffers::Vertex** vertices, size_t count, Usage indices_usage, size_t indices_count = default_indices_count, bool is_reference = true);

	virtual void AddVertexes(const void_ptr_cst* data_ptr, size_t count)override;
protected:
	buffers::Indices _indices;
};

NGS_END
NGL_END
