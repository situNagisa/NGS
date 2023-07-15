#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/buffer.h"
#include "NGS/ngl/base/target.h"
#include "NGS/ngl/gl_enum.h"

NGL_BEGIN

using indices_t = uint32;

NGL_BUF_BEGIN

class Indices : public Buffer {
public:
	Indices(void_ptr data, size_t count, Usage usage);
	Indices(size_t count, Usage usage);
	Indices(Indices&& other)
		: Buffer(std::move(other))
	{}
	~Indices();

	const indices_t* GetData()const { return std::launder(reinterpret_cast<const indices_t*>(_data)); }

	void View(size_t count, size_t offset);
	void Write(const indices_t* data, size_t count, size_t offset);

	constexpr static type_t type = gl_convert<indices_t>;
	constexpr static size_t format_size = sizeof(indices_t);
};

NGS_END
NGL_FAC_BEGIN

template<CTemplateFrom<mpl::meta_struct> _Struct>
buffers::Indices* make_vertex(void_ptr data, size_t count, Usage usage) {
	buffers::Vertex* vertex;
	NGS_NEW(vertex, buffers::Vertex)(data, count, usage, make_vertex_format<_Struct>());
	return vertex;
}

template<CTemplateFrom<mpl::meta_struct> _Struct>
buffers::Indices* make_vertex(size_t count, Usage usage) {
	buffers::Vertex* vertex;
	NGS_NEW(vertex, buffers::Vertex)(count, usage, make_vertex_format<_Struct>());
	return vertex;
}

NGS_END
NGL_END
