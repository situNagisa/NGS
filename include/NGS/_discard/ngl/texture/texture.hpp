#pragma once

#include "NGS/ngl/texture/texture.h"

NGL_BEGIN
NGL_TARGET_BEGIN
NGS_HPP_INLINE void Texture::_Select(state_type* state) {
	if (state->slot != TextureSlot::null)NGL_CHECK(glActiveTexture(static_cast<GLenum>(state->slot)));
	NGL_CHECK(glBindTexture(static_cast<GLenum>(state->target), state->GetContext()));
}
NGS_END


NGL_END
