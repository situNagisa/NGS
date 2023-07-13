#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/context.h"
#include "NGS/ngl/gl/error.h"
#include "NGS/ngl/gl_enum.h"

NGLGL_BEGIN

inline TextureSlot operator+(TextureSlot slot, uint32 offset) { return (TextureSlot)((uint32)slot + offset); }
inline TextureSlot operator-(TextureSlot slot, uint32 offset) { return (TextureSlot)((uint32)slot - offset); }

_NGL_DECALRE_CONTEXT(_Texture, GLuint) {
private:
	static void _GENERATE(handle_type & handle) { glGenTextures(1, &handle); }
	static void _DESTROY(handle_type & handle) { glDeleteTextures(1, &handle); }
public:
	_NGL_CONTEXT_DEFAULT_CONSTRUCTOR(_Texture);
};

_NGL_DECLARE_CURRENT_T(Texture, TextureType) {
	_NGL_CURRENT_DEFAULT_CONSTRUCTOR_T(Texture) { _NGL_CHECK(glBindTexture(type, context)); }
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
