#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class NGS_DLL_API framebuffer_status : gl_enum_t {
	complete = GL_FRAMEBUFFER_COMPLETE,
	undefined = GL_FRAMEBUFFER_UNDEFINED,
	incomplete_attachment = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
	incomplete_missing_attachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
	incomplete_draw_buffer = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
	incomplete_read_buffer = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
	unsupported = GL_FRAMEBUFFER_UNSUPPORTED,
	incomplete_multi_sample = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
	incomplete_layer_targets = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS,
};
enum class NGS_DLL_API framebuffer_attachment : gl_enum_t {
	color0 = GL_COLOR_ATTACHMENT0,
	color1 = GL_COLOR_ATTACHMENT1,
	color2 = GL_COLOR_ATTACHMENT2,
	color3 = GL_COLOR_ATTACHMENT3,
	color4 = GL_COLOR_ATTACHMENT4,
	color5 = GL_COLOR_ATTACHMENT5,
	color6 = GL_COLOR_ATTACHMENT6,
	color7 = GL_COLOR_ATTACHMENT7,
	color8 = GL_COLOR_ATTACHMENT8,
	color9 = GL_COLOR_ATTACHMENT9,
	color10 = GL_COLOR_ATTACHMENT10,
	color11 = GL_COLOR_ATTACHMENT11,
	color12 = GL_COLOR_ATTACHMENT12,
	color13 = GL_COLOR_ATTACHMENT13,
	color14 = GL_COLOR_ATTACHMENT14,
	color15 = GL_COLOR_ATTACHMENT15,
	depth = GL_DEPTH_ATTACHMENT,
	stencil = GL_STENCIL_ATTACHMENT,
	depth_stencil = GL_DEPTH_STENCIL_ATTACHMENT,
};

enum class NGS_DLL_API framebuffer_target : gl_enum_t {
	framebuffer = GL_FRAMEBUFFER,
	read = GL_READ_FRAMEBUFFER,
	draw = GL_DRAW_FRAMEBUFFER,
};

template<class T> requires ::std::is_enum_v<T>
constexpr auto operator|(T left, T right)
{
	return static_cast<T>(static_cast<::std::underlying_type_t<T>>(left) | static_cast<::std::underlying_type_t<T>>(right));
}
template<class T> requires ::std::is_enum_v<T>
constexpr auto operator&(T left, T right)
{
	return static_cast<T>(static_cast<::std::underlying_type_t<T>>(left) & static_cast<::std::underlying_type_t<T>>(right));
}

enum class NGS_DLL_API framebuffer_clear_bit : GLbitfield
{
	color = GL_COLOR_BUFFER_BIT,
	depth = GL_DEPTH_BUFFER_BIT,
	stencil = GL_STENCIL_BUFFER_BIT,
	depth_stencil = GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
};

enum class NGS_DLL_API framebuffer_enable_bit : GLenum
{
	blend = GL_BLEND,
	cull_face = GL_CULL_FACE,
	depth_test = GL_DEPTH_TEST,
	dither = GL_DITHER,
	multi_sample = GL_MULTISAMPLE,
	polygon_offset_fill = GL_POLYGON_OFFSET_FILL,
	sample_alpha_to_coverage = GL_SAMPLE_ALPHA_TO_COVERAGE,
	sample_alpha_to_one = GL_SAMPLE_ALPHA_TO_ONE,
	sample_coverage = GL_SAMPLE_COVERAGE,
	scissor_test = GL_SCISSOR_TEST,
	stencil_test = GL_STENCIL_TEST,
};

NGS_LIB_MODULE_END
