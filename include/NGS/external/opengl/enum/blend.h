#pragma once

#include "./defined.h"

NGS_OPENGL_ENUM_BEGIN

enum class NGS_DLL_API blend_factors : gl_enum_t {
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
enum class NGS_DLL_API blend_equations : gl_enum_t {
	add = GL_FUNC_ADD,
	subtract = GL_FUNC_SUBTRACT,
	reverse_subtract = GL_FUNC_REVERSE_SUBTRACT,
	min = GL_MIN,
	max = GL_MAX,
};

struct NGS_DLL_API blend_mode {
protected:
	using self_type = blend_mode;
public:
	blend_factors source;
	blend_factors destination;
	blend_equations equation;

	constexpr bool operator==(const self_type& other) const {
		return source == other.source && destination == other.destination && equation == other.equation;
	}
};

namespace blend_modes {

	inline constexpr NGS_DLL_API blend_mode normal = { blend_factors::one, blend_factors::zero, blend_equations::add };
	inline constexpr NGS_DLL_API blend_mode alpha = { blend_factors::src_alpha, blend_factors::one_minus_src_alpha, blend_equations::add };
	inline constexpr NGS_DLL_API blend_mode add = { blend_factors::src_alpha, blend_factors::one, blend_equations::add };
	inline constexpr NGS_DLL_API blend_mode subtract = { blend_factors::src_alpha, blend_factors::one, blend_equations::subtract };
	inline constexpr NGS_DLL_API blend_mode multiply = { blend_factors::dst_color, blend_factors::zero, blend_equations::add };
	inline constexpr NGS_DLL_API blend_mode screen = { blend_factors::one, blend_factors::one_minus_src_color, blend_equations::add };
	inline constexpr NGS_DLL_API blend_mode erase = { blend_factors::zero, blend_factors::one_minus_src_alpha, blend_equations::subtract };
	//inline constexpr NGS_DLL_API blend_mode mask = { blend_factors::zero, blend_factors::src_alpha, blend_equations::zero };
	inline constexpr NGS_DLL_API blend_mode below = { blend_factors::one_minus_dst_alpha, blend_factors::dst_alpha, blend_equations::add };

}

NGS_OPENGL_ENUM_END
