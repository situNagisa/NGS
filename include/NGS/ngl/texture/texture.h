#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/base/state.h"
#include "NGS/ngl/error.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/base/target.h"
#include "NGS/ngl/base/opengl.h"
#include "NGS/ngl/texture/image_view.h"

NGL_BEGIN
NGL_OBJ_BEGIN
class NGS_DLL_API  _Texture;
NGS_END

NGL_TARGET_BEGIN

class NGS_DLL_API  Texture : public Target<Texture, objects::_Texture> {
	friend class  Target<Texture, objects::_Texture>;
	static void _Select(state_type* state);
public:

};

NGS_END


NGS_GL_GET_TARGET_FUNCTION(targets::Texture, objects::_Texture, texture);

NGL_OBJ_BEGIN

#undef min

class NGS_DLL_API  _Texture : public State {
public:
	_Texture(TextureTarget target, const ImageView& image, size_t mipmap_level)
		: target(target)
		, _image(image)
	{
		NGL_CHECK(glGenTextures(1, &_context));

		if (_image.IsEmpty())return;
		_UpdateImage(mipmap_level);
	}
	_Texture(
		TextureTarget target,
		void_ptr_cst data,
		size_t width, size_t height,
		format_t format,
		size_t mipmap_level)
		: _Texture(target, { data,width,height,format }, mipmap_level)
	{}

	_Texture(
		TextureTarget target,
		void_ptr_cst data,
		size_t width, size_t height,
		format_t format, internal_format_t internal_format,
		type_t type,
		size_t mipmap_level)
		: _Texture(target, { data,width,height,format,internal_format ,type }, mipmap_level)
	{}

	_Texture(TextureTarget target)
		: _Texture(target, {}, 0)
	{}

	_Texture(_Texture&& other) noexcept
		: State(std::move(other))
		, target(other.target)
		, min(other.min)
		, mag(other.mag)
		, s(other.s)
		, t(other.t)
		, r(other.r)
		, slot(other.slot)
		, _image(std::move(other._image))
	{}

	virtual ~_Texture() override
	{
		if (!_context)return;
		NGL_CHECK(glDeleteTextures(1, &_context));
	}

	void SetImage(const ImageView& image, size_t mipmap_level = 0) {
		_image = image;
		_UpdateImage(mipmap_level);
	}
	ImageView& GetImage() { return _image; }
	const ImageView& GetImage()const { return _image; }

	virtual void Update()override {
		if (!_required_update)return;
		State::Update();
		_UpdateData();
	}
protected:
	void _UpdateData() {
		auto& opengl = OpenGL::I();

		if (!is_bind(this))
			bind(this);

		NGL_CHECK(glTexParameteri(static_cast<GLenum>(target), GL_TEXTURE_WRAP_S, static_cast<GLint>(s)));
		NGL_CHECK(glTexParameteri(static_cast<GLenum>(target), GL_TEXTURE_WRAP_T, static_cast<GLint>(t)));
		NGL_CHECK(glTexParameteri(static_cast<GLenum>(target), GL_TEXTURE_WRAP_R, static_cast<GLint>(r)));
		NGL_CHECK(glTexParameteri(static_cast<GLenum>(target), GL_TEXTURE_MIN_FILTER, static_cast<GLint>(min)));
		NGL_CHECK(glTexParameteri(static_cast<GLenum>(target), GL_TEXTURE_MAG_FILTER, static_cast<GLint>(mag)));

	}
	void _UpdateImage(size_t mipmap_level) {
		if (!is_bind(this))bind(this);
		NGL_CHECK(glTexImage2D(
			static_cast<GLenum>(target),
			static_cast<GLint>(mipmap_level),
			_image.GetInternalFormat(),
			static_cast<GLsizei>(_image.GetSize().x),
			static_cast<GLsizei>(_image.GetSize().y),
			0,
			_image.GetFormat(),
			_image.GetType(),
			_image.GetData()
		));
		NGL_CHECK(glGenerateMipmap(static_cast<GLenum>(target)));
	}
public:
	const TextureTarget target;

	Filters min = Filters::nearest;
	Filters mag = Filters::linear;
	Wraps s = Wraps::clamp_to_edge;
	Wraps t = Wraps::clamp_to_edge;
	Wraps r = Wraps::clamp_to_edge;

	TextureSlot slot = TextureSlot::null;
private:
	ImageView _image;
};

template<TextureTarget _Target>
class NGS_DLL_API  Texture : public _Texture {
public:
	Texture(Texture&&) = default;

	Texture(void_ptr_cst data, size_t width, size_t height, type_t format, size_t mipmap_level = 0)
		: _Texture(_Target, data, width, height, format, mipmap_level)
	{}
	Texture(
		void_ptr_cst data,
		size_t width, size_t height,
		format_t format, internal_format_t internal_format,
		type_t type,
		size_t mipmap_level = 0)
		: _Texture(_Target, data, width, height, format, internal_format, type, mipmap_level)
	{}

	template<cpt::is_any_of<RGBA24, RGBA32> _RGBA>
	Texture(const _RGBA* data, size_t width, size_t height, size_t mipmap_level = 0)
		: Texture(data, width, height, gl_convert<_RGBA>, mipmap_level)
	{}

	Texture(const ImageView& image, size_t mipmap_level = 0)
		: _Texture(_Target, image, mipmap_level)
	{}

	Texture() : _Texture(_Target) {}
};

using Texture1D = Texture<TextureTarget::_1D>;
using Texture2D = Texture<TextureTarget::_2D>;
using Texture3D = Texture<TextureTarget::_3D>;
using Texture1DArray = Texture<TextureTarget::_1D_array>;
using Texture2DArray = Texture<TextureTarget::_2D_array>;
using TextureRectangle = Texture<TextureTarget::_rectangle>;


NGS_END

NGL_END
