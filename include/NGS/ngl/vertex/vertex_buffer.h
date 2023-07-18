#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/buffer.h"
#include "NGS/ngl/vertex/vertex_format.h"
#include "NGS/ngl/error.h"
#include "NGS/ngl/base/opengl.h"

NGL_BEGIN

NGL_BUF_BEGIN

class VertexBuffer : public BufferObject {
public:
	VertexBuffer(void_ptr data, size_t count, Usage usage, const Buffer& format);
	VertexBuffer(size_t count, Usage usage, const Buffer& format);
	VertexBuffer(VertexBuffer&& other)
		: BufferObject(std::move(other))
		, format(other.format)
	{}
	~VertexBuffer() = default;

	void View(size_t count, size_t offset);
	void Write(void_ptr_cst data, size_t count, size_t offset);

	byte_ptr GetData() { return _data; }
	byte_ptr_cst GetData()const { return _data; }

	const Buffer format;
};

NGS_END
NGL_FAC_BEGIN

template<CBuffer _Buffer>
buffers::VertexBuffer make_vertex_buffer(void_ptr data, size_t count, Usage usage) {
	return { data, count, usage, make_buffer<_Buffer>() };
}

template<CBuffer _Buffer>
buffers::VertexBuffer make_vertex_buffer(size_t count, Usage usage) {
	return { count, usage, make_buffer<_Buffer>() };
}

NGS_END
NGL_END
