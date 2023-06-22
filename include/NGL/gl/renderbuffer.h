﻿#pragma once

#include "NGL/defined.h"
#include "NGL/context.h"

NGLGL_BEGIN

enum class RenderbufferImageFormat {
	depth_component = GL_DEPTH_COMPONENT,
	depth_stencil = GL_DEPTH_STENCIL,
	stencil_index = GL_STENCIL_INDEX,
	R8 = GL_R8,
	RG8 = GL_RG8,
	RGB8 = GL_RGB8,
	RGBA8 = GL_RGBA8,
	R16F = GL_R16F,
	RG16F = GL_RG16F,
	RGB16F = GL_RGB16F,
	RGBA16F = GL_RGBA16F,
	R32F = GL_R32F,
	RG32F = GL_RG32F,
	RGB32F = GL_RGB32F,
	RGBA32F = GL_RGBA32F,
	R11FG11FB10F = GL_R11F_G11F_B10F,
	RGB9E5 = GL_RGB9_E5,
	R8I = GL_R8I,
	R8UI = GL_R8UI,
	R16I = GL_R16I,
	R16UI = GL_R16UI,
	R32I = GL_R32I,
	R32UI = GL_R32UI,
	RG8I = GL_RG8I,
	RG8UI = GL_RG8UI,
	RG16I = GL_RG16I,
	RG16UI = GL_RG16UI,
	RG32I = GL_RG32I,
	RG32UI = GL_RG32UI,
	RGB8I = GL_RGB8I,
	RGB8UI = GL_RGB8UI,
	RGB16I = GL_RGB16I,
	RGB16UI = GL_RGB16UI,
	RGB32I = GL_RGB32I,
	RGB32UI = GL_RGB32UI,
	RGBA8I = GL_RGBA8I,
	RGBA8UI = GL_RGBA8UI,
	RGBA16I = GL_RGBA16I,
	RGBA16UI = GL_RGBA16UI,
	RGBA32I = GL_RGBA32I,
	RGBA32UI = GL_RGBA32UI,
	depth_component16 = GL_DEPTH_COMPONENT16,
	depth_component24 = GL_DEPTH_COMPONENT24,
	depth_component32 = GL_DEPTH_COMPONENT32,
	depth_component32F = GL_DEPTH_COMPONENT32F,
	depth24_stencil = GL_DEPTH24_STENCIL8,
	depth32F_stencil8 = GL_DEPTH32F_STENCIL8,
};


_NGL_DECALRE_CONTEXT(Renderbuffer, GLuint) {
public:
	constexpr static GLenum type = GL_RENDERBUFFER;
	RenderbufferContext() { glGenRenderbuffers(1, &_handle); }
	~RenderbufferContext() { glDeleteRenderbuffers(1, &_handle); }
};

_NGL_DECALRE_CURRENT(Renderbuffer) {
	constexpr static auto type = GL_RENDERBUFFER;
	_NGL_CURRENT_DEFAULT_CONSTRUCTOR(Renderbuffer) { glBindRenderbuffer(type, context); }
public:

	void SetStorage(RenderbufferImageFormat internal_format, size_t width, size_t height) {
		glRenderbufferStorage(type, (GLenum)internal_format, width, height);
	}
};

NGLGL_END
