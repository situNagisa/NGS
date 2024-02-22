#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class NGS_DLL_API buffer_target : gl_enum_t {
	array = GL_ARRAY_BUFFER,
	atomic_counter = GL_ATOMIC_COUNTER_BUFFER,
	copy_read = GL_COPY_READ_BUFFER,
	copy_write = GL_COPY_WRITE_BUFFER,
	dispatch_indirect = GL_DISPATCH_INDIRECT_BUFFER,
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

NGS_LIB_MODULE_END