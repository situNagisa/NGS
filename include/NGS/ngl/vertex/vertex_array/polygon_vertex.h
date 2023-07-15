#pragma once

#include "NGS/ngl/vertex/vertex_array/indices_vertex.h"

NGL_BEGIN
NGL_OBJ_BEGIN

class PolygonVertexArray : public IndicesVertexArray
{
public:
	PolygonVertexArray(PolygonVertexArray&&) = default;
	PolygonVertexArray(buffers::Vertex** vertices, size_t count, Usage indices_usage, bool is_reference = true);

	void AddPolygon(const void_ptr_cst* data_ptr, size_t count);

	void AddTriangle(void_ptr_cst point_0, void_ptr_cst point_1, void_ptr_cst point_2) {
		void_ptr_cst triangle[] = { point_0,point_1,point_2 };
		AddPolygon(triangle, 3);
	}
	void AddQuad(void_ptr_cst left_top, void_ptr_cst right_top, void_ptr_cst right_bottom, void_ptr_cst left_bottom) {
		void_ptr_cst quad[] = { left_top,right_top,right_bottom,left_bottom };
		AddPolygon(quad, 4);
	}
};

NGS_END
NGL_END
