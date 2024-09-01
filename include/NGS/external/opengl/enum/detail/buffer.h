#pragma once

#include "./basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class NGS_DLL_API buffer_target : enum_underlying_t {
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

enum class buffer_uniform_fundamental : enum_underlying_t
{
	none = 0,
	integral = GL_INT,
	unsigned_integral = GL_UNSIGNED_INT,
	floating_point = GL_FLOAT,
};

enum class buffer_vertex_fundamental : enum_underlying_t
{
	none = 0,
	floating_point_16 = GL_HALF_FLOAT,
	floating_point_32 = GL_FLOAT,
	floating_point_64 = GL_DOUBLE,
	integral_8 = GL_BYTE,
	integral_16 = GL_SHORT,
	integral_32 = GL_INT,
	unsigned_integral_8 = GL_UNSIGNED_BYTE,
	unsigned_integral_16 = GL_UNSIGNED_SHORT,
	unsigned_integral_32 = GL_UNSIGNED_INT,
};

enum class buffer_indices_fundamental : enum_underlying_t
{
	none = 0,
	unsigned_integral_8 = GL_UNSIGNED_BYTE,
	unsigned_integral_16 = GL_UNSIGNED_SHORT,
	unsigned_integral_32 = GL_UNSIGNED_INT,
};

NGS_LIB_MODULE_END