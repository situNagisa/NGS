#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN


enum class NGS_DLL_API renderbuffer_image_format {
	depth_component = GL_DEPTH_COMPONENT,
	depth_stencil = GL_DEPTH_STENCIL,
	stencil_index = GL_STENCIL_INDEX,
	r8 = GL_R8,
	rg8 = GL_RG8,
	rgb8 = GL_RGB8,
	rgba8 = GL_RGBA8,
	r_16f = GL_R16F,
	rg_16f = GL_RG16F,
	rgb_16f = GL_RGB16F,
	rgba_16f = GL_RGBA16F,
	r_32f = GL_R32F,
	rg_32f = GL_RG32F,
	rgb_32f = GL_RGB32F,
	rgba_32f = GL_RGBA32F,
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
	rg_32i = GL_RG32I,
	rg_32ui = GL_RG32UI,
	rgb_8i = GL_RGB8I,
	rgb_8ui = GL_RGB8UI,
	rgb_16i = GL_RGB16I,
	rgb_16ui = GL_RGB16UI,
	rgb_32i = GL_RGB32I,
	rgb_32ui = GL_RGB32UI,
	rgba_8i = GL_RGBA8I,
	rgba_8ui = GL_RGBA8UI,
	rgba_16i = GL_RGBA16I,
	rgba_16ui = GL_RGBA16UI,
	rgba_32i = GL_RGBA32I,
	rgba_32ui = GL_RGBA32UI,
	depth_component16 = GL_DEPTH_COMPONENT16,
	depth_component24 = GL_DEPTH_COMPONENT24,
	depth_component32 = GL_DEPTH_COMPONENT32,
	depth_component32f = GL_DEPTH_COMPONENT32F,
	depth24_stencil8 = GL_DEPTH24_STENCIL8,
	depth32f_stencil8 = GL_DEPTH32F_STENCIL8,
};

NGS_LIB_MODULE_END
