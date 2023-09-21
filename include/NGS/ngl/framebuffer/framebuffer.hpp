#pragma once

#include "NGS/ngl/framebuffer/framebuffer.h"
#include "NGS/ngl/error.h"
#include "NGS/ngl/base/opengl.h"

NGL_BEGIN
NGL_TARGET_BEGIN

NGS_HPP_INLINE void Framebuffer::_Select(state_type* state)
{
	NGL_CHECK(glBindFramebuffer(static_cast<GLenum>(state->target), state->GetContext()));
}

NGS_HPP_INLINE void Framebuffer::SelectDefault(FramebufferTarget target)
{
	NGL_CHECK(glBindFramebuffer(static_cast<GLenum>(target), 0));
}

NGS_HPP_INLINE bool Framebuffer::CheckComplete(FramebufferTarget target)
{
	GLenum status;
	NGL_CHECK(status = glCheckFramebufferStatus(static_cast<GLenum>(target)));
	return status == GL_FRAMEBUFFER_COMPLETE;
}

NGS_END

NGL_OBJ_BEGIN

NGS_HPP_INLINE void FramebufferBase::Update()
{
	if (!_required_update)return;
	base_type::Update();

	//if(!OpenGL::I().framebuffer->IsState(this))
	//	OpenGL::I().framebuffer->Select(this);
	if (!is_bind(this))
		bind(this);

	for (auto& pair : _attachments) {
		auto& [type, attachment] = pair;
		if (attachment.Empty())continue;
		attachment.Update();
		if (attachment.IsRenderbuffer()) {
			NGL_CHECK(glFramebufferRenderbuffer(
				static_cast<GLenum>(target),
				static_cast<GLenum>(attachment.target),
				static_cast<GLenum>(attachment.GetRenderbuffer()->target),
				attachment.GetRenderbuffer()->GetContext()));
		}
		else if (attachment.IsTexture()) {
			NGL_CHECK(glFramebufferTexture2D(
				static_cast<GLenum>(target),
				static_cast<GLenum>(attachment.target),
				static_cast<GLenum>(attachment.GetTexture()->target),
				attachment.GetTexture()->GetContext(), 0));
		}
	}
}
NGS_END
NGL_END
