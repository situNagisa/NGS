#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/object.h"
#include "NGS/ngl/vertex/vertex.h"
#include "NGS/ngl/error.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/base/opengl.h"

NGL_BEGIN

NGL_OBJ_BEGIN
class VertexArray;
NGS_END

NGL_TARGET_BEGIN

class VertexArray : public Target < VertexArray, objects::VertexArray > {
	friend class base;
	void _Select(state_type* state);
};

NGS_END

NGL_OBJ_BEGIN

class VertexArray : public Object {
public:
	VertexArray(buffers::Vertex** vertices, size_t count, bool is_reference = true);
	VertexArray(VertexArray&& other)
		: Object(std::move(other))
		, _is_reference(other._is_reference)
		, _vertices(other._vertices)
		, _draw_mode(other._draw_mode)
		, _offset(other._offset)
		, _count(other._count)
	{}
	~VertexArray();

	virtual void Update() override;

	void AddVertex(const void_ptr_cst* data_ptr) { AddVertexes(data_ptr, 1); }
	virtual void AddVertexes(const void_ptr_cst* data_ptr, size_t count);

	void SetDrawMode(DrawMode mode) { _draw_mode = (GLenum)mode; }
protected:
	virtual void _Render();
protected:
	bool _is_reference;
	std::vector<buffers::Vertex*> _vertices{};
	GLenum _draw_mode = GL_POINTS;
	size_t _offset = 0;
	size_t _count = 0;
};

NGS_END

NGL_FAC_BEGIN

template<CTemplateFrom<mpl::meta_struct>... _Struct>
objects::VertexArray&& make_vertex_array(size_t count, Usage usage) {
	std::array<buffers::Vertex*, sizeof...(_Struct)> vertices = { new buffers::Vertex(make_vertex<_Struct>(count,usage))... };
	return objects::VertexArray{vertices.data(), count, false};
}

NGS_END

NGL_END
