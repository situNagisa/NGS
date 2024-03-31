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

NGS_LIB_MODULE_END
