#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/base/state.h"
#include "NGS/ngl/error.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/base/target.h"
#include "NGS/ngl/base/opengl.h"

NGL_BEGIN
NGL_OBJ_BEGIN
class _Texture;
NGS_END

NGL_TARGET_BEGIN

class Texture : public Target<Texture, objects::_Texture> {
	friend class base;
	static void _Select(state_type* state);
public:

};

NGS_END

NGL_OBJ_BEGIN

#undef min

class _Texture : public State {
public:
	_Texture(TextureTarget target, void_ptr_cst data, size_t width, size_t height, type_t format, size_t mipmap_level)
		: target(target)
	{
		auto& opengl = OpenGL::I();
		_NGL_CHECK(glGenTextures(1, &_context));
		opengl.texture->Select(this);
		_NGL_CHECK(glTexImage2D((GLenum)target, mipmap_level, format, width, height, 0, format, gl_convert<byte>, data));
		_NGL_CHECK(glGenerateMipmap((GLenum)target));
	}
	_Texture(_Texture&& other)
		: State(std::move(other))
		, target(other.target)
		, min(other.min)
		, mag(other.mag)
		, s(other.s)
		, t(other.t)
		, r(other.r)
		, slot(other.slot)
	{}

	virtual ~_Texture() {
		if (!_context)return;
		_NGL_CHECK(glDeleteTextures(1, &_context));
	}

	virtual void Update()override {
		if (!_required_update)return;
		State::Update();
		_UpdateData();
	}
private:
	void _UpdateData() {
		auto& opengl = OpenGL::I();
		
		if (!opengl.texture->IsState(this))opengl.texture->Select(this);
		_NGL_CHECK(glTexParameteri((GLenum)target, GL_TEXTURE_WRAP_S, (GLint)s));
		_NGL_CHECK(glTexParameteri((GLenum)target, GL_TEXTURE_WRAP_T, (GLint)t));
		_NGL_CHECK(glTexParameteri((GLenum)target, GL_TEXTURE_WRAP_R, (GLint)r));
		_NGL_CHECK(glTexParameteri((GLenum)target, GL_TEXTURE_MIN_FILTER, (GLint)min));
		_NGL_CHECK(glTexParameteri((GLenum)target, GL_TEXTURE_MAG_FILTER, (GLint)mag));

		if(slot != TextureSlot::null)_NGL_CHECK(glActiveTexture((GLenum)slot));
	}
public:
	const TextureTarget target;

	Filters min = Filters::linear_mipmap_linear;
	Filters mag = Filters::linear;
	Wraps s = Wraps::repeat;
	Wraps t = Wraps::repeat;
	Wraps r = Wraps::repeat;

	TextureSlot slot = TextureSlot::null;
};

template<TextureTarget _Target>
class Texture : public _Texture {
public:
	Texture(Texture&&) = default;
	Texture(void_ptr_cst data, size_t width, size_t height, type_t format, size_t mipmap_level = 0) : _Texture(_Target, data, width, height, format, mipmap_level) {}
	template<CSameAsAny<RGBA24, RGBA32> _RGBA>
	Texture(const _RGBA* data, size_t width, size_t height, size_t mipmap_level = 0) : Texture(data, width, height, gl_convert<_RGBA>, mipmap_level) {}
};

using Texture1D = Texture<TextureTarget::_1D>;
using Texture2D = Texture<TextureTarget::_2D>;
using Texture3D = Texture<TextureTarget::_3D>;
using Texture1DArray = Texture<TextureTarget::_1D_array>;
using Texture2DArray = Texture<TextureTarget::_2D_array>;
using TextureRectangle = Texture<TextureTarget::_rectangle>;


NGS_END

NGL_END
