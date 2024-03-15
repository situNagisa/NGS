#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class NGS_DLL_API texture_target : gl_enum_t {
	_1d = GL_TEXTURE_1D,
	_2d = GL_TEXTURE_2D,
	_3d = GL_TEXTURE_3D,
	_1d_array = GL_TEXTURE_1D_ARRAY,
	_2d_array = GL_TEXTURE_2D_ARRAY,
	rectangle = GL_TEXTURE_RECTANGLE,
};
enum class NGS_DLL_API texture_slot : gl_enum_t {
	null = 0,
	_0 = GL_TEXTURE0,
	_1 = GL_TEXTURE1,
	_2 = GL_TEXTURE2,
	_3 = GL_TEXTURE3,
	_4 = GL_TEXTURE4,
	_5 = GL_TEXTURE5,
	_6 = GL_TEXTURE6,
	_7 = GL_TEXTURE7,
	_8 = GL_TEXTURE8,
	_9 = GL_TEXTURE9,
	_10 = GL_TEXTURE10,
	_11 = GL_TEXTURE11,
	_12 = GL_TEXTURE12,
	_13 = GL_TEXTURE13,
	_14 = GL_TEXTURE14,
	_15 = GL_TEXTURE15,
	_16 = GL_TEXTURE16,
	_17 = GL_TEXTURE17,
	_18 = GL_TEXTURE18,
	_19 = GL_TEXTURE19,
	_20 = GL_TEXTURE20,
	_21 = GL_TEXTURE21,
	_22 = GL_TEXTURE22,
	_23 = GL_TEXTURE23,
	_24 = GL_TEXTURE24,
	_25 = GL_TEXTURE25,
	_26 = GL_TEXTURE26,
	_27 = GL_TEXTURE27,
	_28 = GL_TEXTURE28,
	_29 = GL_TEXTURE29,
	_30 = GL_TEXTURE30,
	_31 = GL_TEXTURE31,
	end = _31 + 1,
	begin = _0,
};
constexpr texture_slot operator+(const texture_slot& slot, std::integral auto&& offset) { return static_cast<texture_slot>(static_cast<uint32>(slot) + offset); }
constexpr texture_slot operator-(const texture_slot& slot, std::integral auto&& offset) { return static_cast<texture_slot>(static_cast<uint32>(slot) - offset); }

enum class NGS_DLL_API texture_parameter_name
{
	wrap_s = GL_TEXTURE_WRAP_S,
	wrap_t = GL_TEXTURE_WRAP_T,
	wrap_r = GL_TEXTURE_WRAP_R,
	minify_filter = GL_TEXTURE_MIN_FILTER,
	magnify_filter = GL_TEXTURE_MAG_FILTER,
};

enum class NGS_DLL_API wraps : gl_enum_t {
	repeat = GL_REPEAT,
	mirrored_repeat = GL_MIRRORED_REPEAT,
	clamp_to_edge = GL_CLAMP_TO_EDGE,
	clamp_to_border = GL_CLAMP_TO_BORDER,
};

enum class NGS_DLL_API filters : gl_enum_t {
	nearest = GL_NEAREST,
	linear = GL_LINEAR,
	nearest_mipmap_nearest = GL_NEAREST_MIPMAP_NEAREST,
	linear_mipmap_nearest = GL_LINEAR_MIPMAP_NEAREST,
	nearest_mipmap_linear = GL_NEAREST_MIPMAP_LINEAR,
	linear_mipmap_linear = GL_LINEAR_MIPMAP_LINEAR,
};


enum class NGS_DLL_API internal_format : GLint
{
	red = GL_RED,
	rg = GL_RG,
	rgb = GL_RGB,
	rgba = GL_RGBA,
	depth_component = GL_DEPTH_COMPONENT,
	depth_stencil = GL_DEPTH_STENCIL,
	stencil_index = GL_STENCIL_INDEX,
	r8 = GL_R8,
	rg8 = GL_RG8,
	rgb8 = GL_RGB8,
	rgba8 = GL_RGBA8,
	r16f = GL_R16F,
	rg16f = GL_RG16F,
	rgb16f = GL_RGB16F,
	rgba16f = GL_RGBA16F,
	r32f = GL_R32F,
	rg32f = GL_RG32F,
	rgb32f = GL_RGB32F,
	rgba32f = GL_RGBA32F,
	r11f_g11f_b10f = GL_R11F_G11F_B10F,
	rgb9_e5 = GL_RGB9_E5,
	r8_i = GL_R8I,
	r8_ui = GL_R8UI,
	r16_i = GL_R16I,
	r16_ui = GL_R16UI,
	r32_i = GL_R32I,
	r32_ui = GL_R32UI,
	rg8_i = GL_RG8I,
	rg8_ui = GL_RG8UI,
	rg16_i = GL_RG16I,
	rg16_ui = GL_RG16UI,
	rg32_i = GL_RG32I,
	rg32_ui = GL_RG32UI,
	rgb8_i = GL_RGB8I,
	rgb8_ui = GL_RGB8UI,
	rgb16_i = GL_RGB16I,
	rgb16_ui = GL_RGB16UI,
	rgb32_i = GL_RGB32I,
	rgb32_ui = GL_RGB32UI,
	rgba8_i = GL_RGBA8I,
	rgba8_ui = GL_RGBA8UI,
	rgba16_i = GL_RGBA16I,
	rgba16_ui = GL_RGBA16UI,
	rgba32_i = GL_RGBA32I,
	rgba32_ui = GL_RGBA32UI,
	depth_component16 = GL_DEPTH_COMPONENT16,
	depth_component24 = GL_DEPTH_COMPONENT24,
	depth_component32 = GL_DEPTH_COMPONENT32,
	depth_component32f = GL_DEPTH_COMPONENT32F,
	depth24_stencil8 = GL_DEPTH24_STENCIL8,
	depth32f_stencil8 = GL_DEPTH32F_STENCIL8,
};

enum class format : GLenum
{
	red = GL_RED,
	rg = GL_RG,
	rgb = GL_RGB,
	rgba = GL_RGBA,
	depth_component = GL_DEPTH_COMPONENT,
	depth_stencil = GL_DEPTH_STENCIL,
	stencil_index = GL_STENCIL_INDEX,
};

enum class channel_type : GLenum
{
	unsigned_byte = GL_UNSIGNED_BYTE,
	byte = GL_BYTE,
	unsigned_short = GL_UNSIGNED_SHORT,
	short_ = GL_SHORT,
	unsigned_int = GL_UNSIGNED_INT,
	int_ = GL_INT,
	float32 = GL_FLOAT,
	float64 = GL_DOUBLE,
	unsigned_int_24_8 = GL_UNSIGNED_INT_24_8,
};

NGS_LIB_MODULE_END
