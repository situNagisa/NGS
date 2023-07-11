#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/context.h"
#include "NGS/ngl/gl/error.h"

NGLGL_BEGIN

enum class Wraps : GLint {
	repeat = GL_REPEAT,
	mirrored_repeat = GL_MIRRORED_REPEAT,
	clamp_to_edge = GL_CLAMP_TO_EDGE,
	clamp_to_border = GL_CLAMP_TO_BORDER,
};

enum class Filters : GLint {
	nearest = GL_NEAREST,
	linear = GL_LINEAR,
	nearest_mipmap_nearest = GL_NEAREST_MIPMAP_NEAREST,
	linear_mipmap_nearest = GL_LINEAR_MIPMAP_NEAREST,
	nearest_mipmap_linear = GL_NEAREST_MIPMAP_LINEAR,
	linear_mipmap_linear = GL_LINEAR_MIPMAP_LINEAR,
};

enum class TextureType : GLenum {
	_1D = GL_TEXTURE_1D,
	_2D = GL_TEXTURE_2D,
	_3D = GL_TEXTURE_3D,
	_1D_array = GL_TEXTURE_1D_ARRAY,
	_2D_array = GL_TEXTURE_2D_ARRAY,
	_rectangle = GL_TEXTURE_RECTANGLE,
};
enum class TextureSlot : GLenum {
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
};
inline TextureSlot operator+(TextureSlot slot, uint32 offset) { return (TextureSlot)((uint32)slot + offset); }
inline TextureSlot operator-(TextureSlot slot, uint32 offset) { return (TextureSlot)((uint32)slot - offset); }

_NGL_DECALRE_CONTEXT(_Texture, GLuint) {
public:
	_TextureContext() { _NGL_CHECK(glGenTextures(1, &_handle)); }
	~_TextureContext() { _NGL_CHECK(glDeleteTextures(1, &_handle)); }
};

_NGL_DECLARE_CURRENT_T(Texture, TextureType) {
	_NGL_CURRENT_DEFAULT_CONSTRUCTOR_T(Texture) { glBindTexture(type, context); }
public:
	void Generate(void_ptr_cst data, GLsizei width, GLsizei height, GLenum element_t, GLint internalFormat, GLenum format, GLint level = 0) {
		_NGL_CHECK(glTexImage2D(type, level, internalFormat, width, height, 0, format, element_t, data));
	}
	template<class _CacheAs = byte, CARGB _ARGB>
	void Generate(const _ARGB * data, size_t width, size_t height, int level = 0) {
		Generate(data, width, height, gl_convert<_CacheAs>, gl_convert<_ARGB>, gl_convert<_ARGB>, level);
	}
	void GenerateMipmap() { _NGL_CHECK(glGenerateMipmap(type)); }

	void Active(TextureSlot slot = TextureSlot::_0) { _NGL_CHECK(glActiveTexture((GLenum)slot)); }
	void Active(uint32 offset) { Active(TextureSlot::_0 + offset); }

	void SetParameter(GLenum property, GLint value) { _NGL_CHECK(glTexParameteri(type, property, value)); }
	void SetParameter(GLenum property, GLfloat value) { _NGL_CHECK(glTexParameterf(type, property, value)); }

	void SetWrapS(Wraps value) { SetParameter(GL_TEXTURE_WRAP_S, (GLint)value); }
	void SetWrapT(Wraps value) { SetParameter(GL_TEXTURE_WRAP_T, (GLint)value); }
	void SetWrapR(Wraps value) { SetParameter(GL_TEXTURE_WRAP_R, (GLint)value); }
	void SetWrap(Wraps value) { SetWrapS(value); SetWrapT(value); SetWrapR(value); }
	void SetWrap(Wraps s, Wraps t) { SetWrapS(s); SetWrapT(t); }
	void SetWrap(Wraps s, Wraps t, Wraps r) { SetWrapS(s); SetWrapT(t); SetWrapR(r); }

	void SetMinFilter(Filters value) { SetParameter(GL_TEXTURE_MIN_FILTER, (GLint)value); }
	void SetMagFilter(Filters value) { SetParameter(GL_TEXTURE_MAG_FILTER, (GLint)value); }
	void SetFilter(Filters value) { SetMinFilter(value); SetMagFilter(value); }
	void SetFilter(Filters min, Filters mag) { SetMinFilter(min); SetMagFilter(mag); }
};

_NGL_SPECIALIZATION(Texture, TextureType::_1D, Texture1D, texture_1d);
_NGL_SPECIALIZATION(Texture, TextureType::_2D, Texture2D, texture_2d);
_NGL_SPECIALIZATION(Texture, TextureType::_3D, Texture3D, texture_3d);
_NGL_SPECIALIZATION(Texture, TextureType::_1D_array, Texture1DArray, texture_1d_array);
_NGL_SPECIALIZATION(Texture, TextureType::_2D_array, Texture2DArray, texture_2d_array);
_NGL_SPECIALIZATION(Texture, TextureType::_rectangle, TextureRectangle, texture_rectangle);

NGLGL_END
