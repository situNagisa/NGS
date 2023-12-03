#pragma once

#include "NGS/ngl/error.h"
#include "NGS/ngl/framebuffer/renderbuffer.h"
#include "NGS/ngl/base/opengl.h"

NGL_BEGIN
NGL_TARGET_BEGIN

NGS_HPP_INLINE void Renderbuffer::_Select(state_type* state)
{
	NGL_CHECK(glBindRenderbuffer(static_cast<GLenum>(state->target), state->GetContext()));
}

NGS_END

NGL_OBJ_BEGIN

NGS_HPP_INLINE void Renderbuffer::Update()
{
	if (!_required_update)return;
	Object::Update();

	if (!is_bind(this)) {
		bind(this);
	}

	NGL_CHECK(glRenderbufferStorage(
		static_cast<GLenum>(target),
		static_cast<GLenum>(_format),
		static_cast<GLsizei>(_size.x), static_cast<GLsizei>(_size.y)));
}
NGS_END
NGL_END
