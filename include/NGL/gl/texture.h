#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"
#include "NGL/context.h"

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

_NGL_DECALRE_CONTEXT(_Texture, GLuint) {
public:
	_TextureContext() { glGenTextures(1, &_handle); }
	~_TextureContext() { glDeleteTextures(1, &_handle); }
};

_NGL_DECLARE_CURRENT_T(Texture, TextureType) {
	_NGL_CURRENT_DEFAULT_CONSTRUCTOR_T(Texture) { glBindTexture(type, context); }
public:
	void Generate(void_ptr_cst data, GLsizei width, GLsizei height, GLenum element_t, GLint internalFormat, GLenum format, GLint level = 0) {
		glTexImage2D(type, level, internalFormat, width, height, 0, format, element_t, data);
	}
	template<class _CacheAs = byte, ARGB_C _ARGB>
	void Generate(const _ARGB * data, size_t width, size_t height, int level = 0) {
		Generate(data, width, height, convert<_CacheAs>, convert<_ARGB>, convert<_ARGB>, level);
	}
	void GenerateMipmap() { glGenerateMipmap(type); }

	void SetParameter(GLenum property, GLint value) { glTexParameteri(type, property, value); }
	void SetParameter(GLenum property, GLfloat value) { glTexParameterf(type, property, value); }

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
