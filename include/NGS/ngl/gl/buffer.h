﻿#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/context.h"
#include "NGS/ngl/gl/error.h"
#include "NGS/ngl/gl/vertex.h"

NGLGL_BEGIN

enum class BufferTarget : GLenum {
	array = GL_ARRAY_BUFFER,
	atomic_counter = GL_ATOMIC_COUNTER_BUFFER,
	copy_read = GL_COPY_READ_BUFFER,
	copy_write = GL_COPY_WRITE_BUFFER,
	dispatch_indriect = GL_DISPATCH_INDIRECT_BUFFER,
	draw_indirect = GL_DRAW_INDIRECT_BUFFER,
	element = GL_ELEMENT_ARRAY_BUFFER,
	pixel_pack = GL_PIXEL_PACK_BUFFER,
	pixel_unpack = GL_PIXEL_UNPACK_BUFFER,
	query = GL_QUERY_BUFFER,
	shader_storage = GL_SHADER_STORAGE_BUFFER,
	texture = GL_TEXTURE_BUFFER,
	transform_feedback = GL_TRANSFORM_FEEDBACK_BUFFER,
	uniform = GL_UNIFORM_BUFFER,
};
enum class BufferUsage : GLenum {
	stream_draw = GL_STREAM_DRAW,
	stream_read = GL_STREAM_READ,
	stream_copy = GL_STREAM_COPY,

	static_draw = GL_STATIC_DRAW,
	static_read = GL_STATIC_READ,
	static_copy = GL_STATIC_COPY,

	dynamic_draw = GL_DYNAMIC_DRAW,
	dynamic_read = GL_DYNAMIC_READ,
	dynamic_copy = GL_DYNAMIC_COPY,
};
enum class BufferDrawMode : GLenum {
	points = GL_POINTS,
	lines = GL_LINES,
	line_strip = GL_LINE_STRIP,
	line_loop = GL_LINE_LOOP,
	triangles = GL_TRIANGLES,
	triangle_strip = GL_TRIANGLE_STRIP,
	triangle_fan = GL_TRIANGLE_FAN,
	patches = GL_PATCHES,
};
enum class DrawMode : GLenum {
	points = GL_POINTS,
	line_strip = GL_LINE_STRIP,
	line_loop = GL_LINE_LOOP,
	lines = GL_LINES,
	line_strip_adjacency = GL_LINE_STRIP_ADJACENCY,
	lines_adjacency = GL_LINES_ADJACENCY,
	triangle_strip = GL_TRIANGLE_STRIP,
	triangle_fan = GL_TRIANGLE_FAN,
	triangles = GL_TRIANGLES,
	triangle_strip_adjacency = GL_TRIANGLE_STRIP_ADJACENCY,
	triangles_adjacency = GL_TRIANGLES_ADJACENCY,
};

_NGL_DECALRE_CONTEXT(_Buffer, GLuint) {
public:
	_BufferContext() { glGenBuffers(1, &this->_handle); }
	~_BufferContext() { glDeleteBuffers(1, &this->_handle); this->_handle = 0; }
};

_NGL_DECLARE_CURRENT_T(Buffer, BufferTarget) {
	_NGL_CURRENT_DEFAULT_CONSTRUCTOR_T(Buffer) { glBindBuffer(type, context); }
public:

	void SetData(void_ptr_cst data, size_t size, BufferUsage usage = BufferUsage::static_draw) { _NGL_CHECK(glBufferData(type, size, data, (GLenum)usage)); }
	void SetData(std::ranges::random_access_range auto && data, BufferUsage usage = BufferUsage::static_draw) {
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

