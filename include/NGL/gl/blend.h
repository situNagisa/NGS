#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/gl/state.h"

NGLGL_BEGIN

enum class BlendFactors : GLenum {
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
enum class BlendEquations : GLenum {
	add = GL_FUNC_ADD,
	subtract = GL_FUNC_SUBTRACT,
	reverse_subtract = GL_FUNC_REVERSE_SUBTRACT,
	min = GL_MIN,
	max = GL_MAX,
};

class Blend : DeleteCopy {
public:
	Capabilities capability = Capabilities::blend;
private:
	friend class Constructor;
	Blend() = default;
public:
	void Func(BlendFactors src, BlendFactors dst);
	void FuncSeparate(BlendFactors srcRGB, BlendFactors dstRGB, BlendFactors srcAlpha, BlendFactors dstAlpha);
	void Equation(BlendEquations mode);
	void EquationSeparate(BlendEquations modeRGB, BlendEquations modeAlpha);
};
inline static auto blender = Constructor::Construct<Blend>();

NGLGL_END
