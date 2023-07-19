#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/context.h"
#include "NGS/ngl/gl/state.h"
#include "NGS/ngl/gl/texture.h"
#include "NGS/ngl/gl/renderbuffer.h"
#include "NGS/ngl/gl/error.h"
#include "NGS/ngl/gl_enum.h"

NGLGL_BEGIN

_NGL_DECALRE_CONTEXT(_Framebuffer, GLuint) {
private:
	static void _GENERATE(handle_type & handle) { glGenFramebuffers(1, &handle); }
	static void _DESTROY(handle_type & handle) { glDeleteFramebuffers(1, &handle); }
public:
	_NGL_CONTEXT_DEFAULT_CONSTRUCTOR(_Framebuffer);
};

_NGL_DECLARE_CURRENT_T(Framebuffer, FramebufferType) {
	_NGL_CURRENT_DEFAULT_CONSTRUCTOR_T(Framebuffer) { _NGL_CHECK(glBindFramebuffer(_Type, context)); }
public:
	FramebufferStatus GetStatus()const { return (FramebufferStatus)glCheckFramebufferStatus(_Type); }
	bool IsComplete()const { return GetStatus() == FramebufferStatus::complete; }

	void AttachRenderbuffer(FramebufferAttachment attachment, const RenderbufferContext & renderbuffer) {
		//NGL_CHECK(glFramebufferRenderbuffer(_Type, (GLenum)attachment, renderbuffer.type, renderbuffer.GetHandle()));
	}
	template<TextureType _Dim>
	void AttachTexture(FramebufferAttachment attachment, const TextureContext<_Dim>&texture, GLint level = 0) {
		_NGL_CHECK(glFramebufferTexture2D(_Type, (GLenum)attachment, texture.type, texture.GetHandle(), level));
	}

};
_NGL_SPECIALIZATION(Framebuffer, FramebufferType::framebuffer, FramebufferNormal, framebuffer);
_NGL_SPECIALIZATION(Framebuffer, FramebufferType::read, FramebufferRead, read);
_NGL_SPECIALIZATION(Framebuffer, FramebufferType::draw, FramebufferDraw, draw);

NGLGL_END
