#pragma once

#include "NGS/ngl/vertex/vertex.h"

NGL_BEGIN

NGL_BUF_BEGIN

NGS_HPP_INLINE Vertex::Vertex(void_ptr data, size_t count, Usage usage, const VertexFormat& format)
	: Buffer(BufferTarget::array, data, count* format.size, usage)
	, format(format)
{}
NGS_HPP_INLINE Vertex::Vertex(size_t count, Usage usage, const VertexFormat& format)
	: Buffer(BufferTarget::array, count* format.size, usage)
	, format(format)
{}

NGS_HPP_INLINE void Vertex::View(size_t count, size_t offset) { Buffer::View(count * format.size, offset * format.size); }
NGS_HPP_INLINE void Vertex::Write(void_ptr_cst data, size_t count, size_t offset) { Buffer::Write(data, count * format.size, offset * format.size); }

NGS_END
NGL_END
