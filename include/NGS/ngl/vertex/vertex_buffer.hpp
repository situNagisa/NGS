#pragma once

#include "NGS/ngl/vertex/vertex.h"

NGL_BEGIN

NGL_BUF_BEGIN

NGS_HPP_INLINE VertexBuffer::VertexBuffer(void_ptr data, size_t count, Usage usage, const Buffer& format)
	: BufferObject(BufferTarget::array, data, count* format.size, usage)
	, format(format)
{}
NGS_HPP_INLINE VertexBuffer::VertexBuffer(size_t count, Usage usage, const Buffer& format)
	: BufferObject(BufferTarget::array, count* format.size, usage)
	, format(format)
{}

NGS_HPP_INLINE void VertexBuffer::View(size_t count, size_t offset) { BufferObject::View(count * format.size, offset * format.size); }
NGS_HPP_INLINE void VertexBuffer::Write(void_ptr_cst data, size_t count, size_t offset) { BufferObject::Write(data, count * format.size, offset * format.size); }

NGS_END
NGL_END
