#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/buffer.h"
#include "NGS/ngl/error.h"
#include "NGS/ngl/base/opengl.h"
#include "./fusion.h"

NGL_BEGIN

NGL_BUF_BEGIN

class NGS_API  VertexBuffer : public BufferObject {
private:
	using base_type = BufferObject;
public:
	
	VertexBuffer(void_ptr data, size_t count, Usage usage, const fusion::buffer_dynamic_data& format);
	VertexBuffer(size_t count, Usage usage, const fusion::buffer_dynamic_data& format);
	VertexBuffer(VertexBuffer&& other) noexcept
		: base_type(std::move(other))
		  , format(other.format)
	{}
	virtual ~VertexBuffer() override = default;

	void View(size_t count, size_t offset);
	void Write(void_ptr_cst data, size_t count, size_t offset);

	void Resize(size_t count);
	void Resize(size_t count, Usage usage);

	void SetUsage(Usage usage);

	byte_ptr GetData() { return _data; }
	byte_ptr_cst GetData()const { return _data; }

	const fusion::buffer_dynamic_data format;
};

NGS_END
NGL_FAC_BEGIN

template<fusion::CBuffer _Buffer>
buffers::VertexBuffer make_vertex_buffer(void_ptr data, size_t count, Usage usage) {
	return { data, count, usage, fusion::make_buffer<_Buffer>() };
}

template<fusion::CBuffer _Buffer>
buffers::VertexBuffer make_vertex_buffer(size_t count, Usage usage) {
	return { count, usage, fusion::make_buffer<_Buffer>() };
}

NGS_END
NGL_END
