#pragma once

#include "NGS/ngl/defined.h"

NGL_BEGIN

enum class TextureTarget : GLenum {
	_1D = GL_TEXTURE_1D,
	_2D = GL_TEXTURE_2D,
	_3D = GL_TEXTURE_3D,
	_1D_array = GL_TEXTURE_1D_ARRAY,
	_2D_array = GL_TEXTURE_2D_ARRAY,
	_rectangle = GL_TEXTURE_RECTANGLE,
};
enum class TextureSlot : GLenum {
	null = 0,
	_0 = GL_TEXTURE0,
	_1 = GL_TEXTURE1,
	_2 = GL_TEXTURE2,
	_3 = GL_TEXTURE3,
	_4 = GL_TEXTURE4,
	_5 = GL_TEXTURE5,
	_6 = GL_TEXTURE6,
	_7 = GL_TEXTURE7,
	_8 = GL_TEXTURE8,
	_9 = GL_TEXTURE9,
	_10 = GL_TEXTURE10,
	_11 = GL_TEXTURE11,
	_12 = GL_TEXTURE12,
	_13 = GL_TEXTURE13,
	_14 = GL_TEXTURE14,
	_15 = GL_TEXTURE15,
	_16 = GL_TEXTURE16,
	_17 = GL_TEXTURE17,
	_18 = GL_TEXTURE18,
	_19 = GL_TEXTURE19,
	_20 = GL_TEXTURE20,
	_21 = GL_TEXTURE21,
	_22 = GL_TEXTURE22,
	_23 = GL_TEXTURE23,
	_24 = GL_TEXTURE24,
	_25 = GL_TEXTURE25,
	_26 = GL_TEXTURE26,
	_27 = GL_TEXTURE27,
	_28 = GL_TEXTURE28,
	_29 = GL_TEXTURE29,
	_30 = GL_TEXTURE30,
	_31 = GL_TEXTURE31,
	end = _31 + 1,
	begin = _0,
};
inline TextureSlot operator+(TextureSlot slot, uint32 offset) { return (TextureSlot)((uint32)slot + offset); }
inline TextureSlot operator-(TextureSlot slot, uint32 offset) { return (TextureSlot)((uint32)slot - offset); }


NGL_END
