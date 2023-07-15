#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/buffer.h"
#include "NGS/ngl/vertex/vertex_format.h"
#include "NGS/ngl/error.h"
#include "NGS/ngl/base/opengl.h"

NGL_BEGIN

NGL_BUF_BEGIN

class Vertex : public Buffer {
public:
	Vertex(void_ptr data, size_t count, Usage usage, const VertexFormat& format);
	Vertex(size_t count, Usage usage, const VertexFormat& format);
	Vertex(Vertex&& other)
		: Buffer(std::move(other))
		, format(other.format)
	{}
	~Vertex();

	void View(size_t count, size_t offset);
	void Write(void_ptr_cst data, size_t count, size_t offset);

	const VertexFormat format;
};

NGS_END
NGL_FAC_BEGIN

template<CTemplateFrom<mpl::meta_struct> _Struct>
buffers::Vertex&& make_vertex(void_ptr data, size_t count, Usage usage) {
	return buffers::Vertex(data, count, usage, make_vertex_format<_Struct>());
}

template<CTemplateFrom<mpl::meta_struct> _Struct>
buffers::Vertex&& make_vertex(size_t count, Usage usage) {
	return buffers::Vertex(count, usage, make_vertex_format<_Struct>());
}

NGS_END
NGL_END
