#pragma once

#include "NGS/ngl/vertex/vertex.h"

NGL_BEGIN

NGL_BUF_BEGIN

NGS_HPP_INLINE VertexBuffer::VertexBuffer(void_ptr data, size_t count, Usage usage, const fusion::buffer_dynamic_data& format)
	: base_type(BufferTarget::array, data, count* format.size, usage)
	, format(format)
{}
NGS_HPP_INLINE VertexBuffer::VertexBuffer(size_t count, Usage usage, const fusion::buffer_dynamic_data& format)
	: base_type(BufferTarget::array, count* format.size, usage)
	, format(format)
{}

NGS_HPP_INLINE void VertexBuffer::View(size_t count, size_t offset)
{
	base_type::View(count * format.size, offset * format.size);
}
NGS_HPP_INLINE void VertexBuffer::Write(void_ptr_cst data, size_t count, size_t offset)
{
	base_type::Write(data, count * format.size, offset * format.size);
}

NGS_HPP_INLINE void VertexBuffer::Resize(size_t count)
{
	base_type::Resize(count * format.size);
}

NGS_HPP_INLINE void VertexBuffer::Resize(size_t count, Usage usage)
{
	base_type::Resize(count * format.size, usage);
}

NGS_HPP_INLINE void VertexBuffer::SetUsage(Usage usage)
{
	base_type::SetUsage(usage);
}

NGS_END

NGL_END
