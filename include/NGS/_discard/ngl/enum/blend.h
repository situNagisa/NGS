﻿#pragma once

#include "NGS/ngl/defined.h"

NGL_BEGIN

enum class  BlendFactors : GLenum {
	zero = GL_ZERO,
	one = GL_ONE,
	src_color = GL_SRC_COLOR,
	one_minus_src_color = GL_ONE_MINUS_SRC_COLOR,
	dst_color = GL_DST_COLOR,
	one_minus_dst_color = GL_ONE_MINUS_DST_COLOR,
	src_alpha = GL_SRC_ALPHA,
	one_minus_src_alpha = GL_ONE_MINUS_SRC_ALPHA,
	dst_alpha = GL_DST_ALPHA,
	one_minus_dst_alpha = GL_ONE_MINUS_DST_ALPHA,
	constant_color = GL_CONSTANT_COLOR,
	one_minus_constant_color = GL_ONE_MINUS_CONSTANT_COLOR,
	constant_alpha = GL_CONSTANT_ALPHA,
	one_minus_constant_alpha = GL_ONE_MINUS_CONSTANT_ALPHA,
	src_alpha_saturate = GL_SRC_ALPHA_SATURATE,
};
enum class  BlendEquations : GLenum {
	add = GL_FUNC_ADD,
	subtract = GL_FUNC_SUBTRACT,
	reverse_subtract = GL_FUNC_REVERSE_SUBTRACT,
	min = GL_MIN,
	max = GL_MAX,
};

struct NGS_DLL_API BlendMode {
	BlendFactors src_factor;
	BlendFactors dst_factor;
	BlendEquations equation;

	constexpr bool operator==(const BlendMode& other) const {
		return src_factor == other.src_factor && dst_factor == other.dst_factor && equation == other.equation;
	}
};

namespace blend_mode {

constexpr static BlendMode normal = { BlendFactors::one, BlendFactors::zero, BlendEquations::add };
constexpr static BlendMode alpha = { BlendFactors::src_alpha, BlendFactors::one_minus_src_alpha, BlendEquations::add };
constexpr static BlendMode add = { BlendFactors::src_alpha, BlendFactors::one, BlendEquations::add };
constexpr static BlendMode subtract = { BlendFactors::src_alpha, BlendFactors::one, BlendEquations::subtract };
constexpr static BlendMode multiply = { BlendFactors::dst_color, BlendFactors::zero, BlendEquations::add };
constexpr static BlendMode screen = { BlendFactors::one, BlendFactors::one_minus_src_color, BlendEquations::add };
constexpr static BlendMode erase = { BlendFactors::zero, BlendFactors::one_minus_src_alpha, BlendEquations::subtract };
//constexpr static BlendMode mask = { BlendFactors::zero, BlendFactors::src_alpha, BlendEquations::zero };
constexpr static BlendMode below = { BlendFactors::one_minus_dst_alpha, BlendFactors::dst_alpha, BlendEquations::add };

}

NGL_END
