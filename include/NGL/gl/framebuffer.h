#pragma once

#include "NGL/defined.h"
#include "NGL/context.h"
#include "NGL/gl/state.h"
#include "NGL/gl/texture.h"
#include "NGL/gl/renderbuffer.h"

NGLGL_BEGIN

enum class FramebufferStatus : GLenum {
	complete = GL_FRAMEBUFFER_COMPLETE,
	undefined = GL_FRAMEBUFFER_UNDEFINED,
	incomplete_attachment = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
	incomplete_missing_attachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
	incomplete_draw_buffer = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
	incomplete_read_buffer = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
	unsupported = GL_FRAMEBUFFER_UNSUPPORTED,
	incomplete_multisample = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
	incomplete_layer_targets = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS,
};
enum class FramebufferAttachment : GLenum {
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

enum class FramebufferType : GLenum {
	framebuffer = GL_FRAMEBUFFER,
	read = GL_READ_FRAMEBUFFER,
	draw = GL_DRAW_FRAMEBUFFER,
};

_NGL_DECALRE_CONTEXT(_Framebuffer, GLuint) {
public:
	_FramebufferContext() { glGenFramebuffers(1, &_handle); }
	~_FramebufferContext() { glDeleteFramebuffers(1, &_handle); }
};

_NGL_DECLARE_CURRENT_T(Framebuffer, FramebufferType) {
	_NGL_CURRENT_DEFAULT_CONSTRUCTOR_T(Framebuffer) { glBindFramebuffer(_Type, context); }
public:
	FramebufferStatus GetStatus()const { return (FramebufferStatus)glCheckFramebufferStatus(_Type); }
	bool IsComplete()const { return GetStatus() == FramebufferStatus::complete; }

	void AttachRenderbuffer(FramebufferAttachment attachment, const RenderbufferContext & renderbuffer) {
		glFramebufferRenderbuffer(_Type, (GLenum)attachment, renderbuffer.type, renderbuffer.GetHandle());
	}
	template<TextureType _Dim>
	void AttachTexture(FramebufferAttachment attachment, const TextureContext<_Dim>&texture, GLint level = 0) {
		glFramebufferTexture2D(_Type, (GLenum)attachment, texture.type, texture.GetHandle(), level);
	}

};
_NGL_SPECIALIZATION(Framebuffer, FramebufferType::framebuffer, FramebufferNormal, framebuffer);
_NGL_SPECIALIZATION(Framebuffer, FramebufferType::read, FramebufferRead, read);
_NGL_SPECIALIZATION(Framebuffer, FramebufferType::draw, FramebufferDraw, draw);

NGLGL_END
