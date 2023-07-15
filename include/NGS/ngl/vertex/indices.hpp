#pragma once

#include "NGS/ngl/vertex/indices.h"

NGL_BEGIN
NGL_BUF_BEGIN

NGS_HPP_INLINE Indices::Indices(void_ptr data, size_t count, Usage usage)
	: Buffer(BufferTarget::element, data, count* format_size, usage)
{}

NGS_HPP_INLINE Indices::Indices(size_t count, Usage usage)
	: Buffer(BufferTarget::element, count* format_size, usage)
{}

NGS_HPP_INLINE void Indices::View(size_t count, size_t offset) {
	Buffer::View(count * format_size, offset * format_size);
}

NGS_HPP_INLINE void Indices::Write(const indices_t* data, size_t count, size_t offset)
{
	Buffer::Write(data, count * format_size, offset * format_size);
}



NGS_END
NGL_END
