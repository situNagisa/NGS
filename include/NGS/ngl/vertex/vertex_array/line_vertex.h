#pragma once

#include "NGS/ngl/vertex/vertex_array/indices_vertex.h"

NGL_BEGIN
NGL_OBJ_BEGIN

class LineVertexArray : public IndicesVertexArray
{
public:
	LineVertexArray(LineVertexArray&&) = default;
	LineVertexArray(buffers::Vertex** vertices, size_t count, Usage indices_usage, bool is_reference = true);

	void AddBrokenLine(const void_ptr_cst* data_ptr, size_t count);
	void AddLine(void_ptr_cst start, void_ptr_cst end) {
		void_ptr_cst lines[] = { start,end };
		AddBrokenLine(lines, 2);
	}
};

NGS_END
NGL_END
