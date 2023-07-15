#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/context.h"
#include "NGS/ngl/gl/error.h"
#include "NGS/ngl/gl/vertex.h"
#include "NGS/ngl/gl_enum.h"

NGLGL_BEGIN

_NGL_DECALRE_CONTEXT(_Buffer, GLuint) {
private:
	static void _GENERATE(handle_type & handle) { glGenBuffers(1, &handle); }
	static void _DESTROY(handle_type & handle) { glDeleteBuffers(1, &handle); }
public:
	_NGL_CONTEXT_DEFAULT_CONSTRUCTOR(_Buffer);
};

_NGL_DECLARE_CURRENT_T(Buffer, BufferTarget) {
	_NGL_CURRENT_DEFAULT_CONSTRUCTOR_T(Buffer) { _NGL_CHECK(glBindBuffer(type, context)); }
public:

	void SetData(void_ptr_cst data, size_t size, Usage usage = Usage::static_draw) { _NGL_CHECK(glBufferData(type, size, data, (GLenum)usage)); }
	void SetData(std::ranges::random_access_range auto && data, Usage usage = Usage::static_draw) {
		SetData(std::ranges::cdata(data), std::ranges::size(data) * sizeof(std::ranges::range_value_t<decltype(data)>), usage);
	}
	void UpdateData(void_ptr_cst data, size_t offset, size_t size) { _NGL_CHECK(glBufferSubData(type, offset, size, data)); }
	void UpdateData(void_ptr_cst data, size_t size) { UpdateData(data, 0, size); }

};

_NGL_SPECIALIZATION(Buffer, BufferTarget::array, ArrayBuffer, array_buffer);
_NGL_SPECIALIZATION(Buffer, BufferTarget::atomic_counter, AtomicCounterBuffer, atomic_counter_buffer);
_NGL_SPECIALIZATION(Buffer, BufferTarget::copy_read, CopyReadBuffer, copy_read_buffer);
_NGL_SPECIALIZATION(Buffer, BufferTarget::copy_write, CopyWriteBuffer, copy_write_buffer);
_NGL_SPECIALIZATION(Buffer, BufferTarget::dispatch_indriect, DispatchIndirectBuffer, dispatch_indirect_buffer);
_NGL_SPECIALIZATION(Buffer, BufferTarget::draw_indirect, DrawIndirectBuffer, draw_indirect_buffer);
_NGL_SPECIALIZATION(Buffer, BufferTarget::element, ElementBuffer, element_buffer);
_NGL_SPECIALIZATION(Buffer, BufferTarget::pixel_pack, PixelPackBuffer, pixel_pack_buffer);
_NGL_SPECIALIZATION(Buffer, BufferTarget::pixel_unpack, PixelUnpackBuffer, pixel_unpack_buffer);
_NGL_SPECIALIZATION(Buffer, BufferTarget::query, QueryBuffer, query_buffer);
_NGL_SPECIALIZATION(Buffer, BufferTarget::shader_storage, ShaderStorageBuffer, shader_storage_buffer);
_NGL_SPECIALIZATION(Buffer, BufferTarget::texture, TextureBuffer, texture_buffer);
_NGL_SPECIALIZATION(Buffer, BufferTarget::transform_feedback, TransformFeedbackBuffer, transform_feedback_buffer);
_NGL_SPECIALIZATION(Buffer, BufferTarget::uniform, UniformBuffer, uniform_buffer);

#undef DECLARE_BUFFER

NGLGL_END


