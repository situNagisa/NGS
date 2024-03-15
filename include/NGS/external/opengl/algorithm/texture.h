#pragma once

#include "../reflect.h"
#include "../error.h"
#include "../enum.h"
#include "../context.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class Type,bool IsPointer>
	struct texture_parameter_functor;

	template<>
	struct texture_parameter_functor< GLfloat,false>
	{
		inline static auto&& value = ::glTexParameterf;
	};

	template<>
	struct texture_parameter_functor<GLfloat, true>
	{
		inline static auto&& value = ::glTexParameterfv;
	};

	template<>
	struct texture_parameter_functor<GLint, false>
	{
		inline static auto&& value = ::glTexParameteri;
	};

	template<>
	struct texture_parameter_functor<GLint, true>
	{
		inline static auto&& value = ::glTexParameteriv;
	};

	template<class ParameterType>
	auto texture_get_parameter_functor()
	{
		using parameter_type = type_traits::naked_t<ParameterType>;
		using value_type = type_traits::naked_t<::std::remove_pointer_t<parameter_type>>;
		return texture_parameter_functor<value_type, ::std::is_pointer_v<parameter_type>>::value;
	}
	template<enums::texture_parameter_name Name,auto Texture>
	void texture_parameter_impl(const contexts::basic_texture<Texture>& texture,auto&& param)
	{
		auto gl_texture_parameter = _detail::texture_get_parameter_functor<decltype(param)>();
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(texture);
		NGS_EXTERNAL_OPENGL_CHECK(gl_texture_parameter(static_cast<gl_enum_t>(type_traits::object_t<decltype(texture)>::target), static_cast<gl_enum_t>(Name), NGS_PP_PERFECT_FORWARD(param)));
	}

	template<enums::texture_parameter_name Name, auto Texture>
	decltype(auto) texture_parameter(const contexts::basic_texture<Texture>& texture, GLfloat param)
	{
		return _detail::texture_parameter_impl<Name>(texture, param);
	}
	template<enums::texture_parameter_name Name, auto Texture>
	decltype(auto) texture_parameter(const contexts::basic_texture<Texture>& texture, const GLfloat* param)
	{
		return _detail::texture_parameter_impl<Name>(texture, param);
	}
	template<enums::texture_parameter_name Name, auto Texture>
	decltype(auto) texture_parameter(const contexts::basic_texture<Texture>& texture, GLint param)
	{
		return _detail::texture_parameter_impl<Name>(texture, param);
	}
	template<enums::texture_parameter_name Name, auto Texture>
	decltype(auto) texture_parameter(const contexts::basic_texture<Texture>& texture, const GLint* param)
	{
		return _detail::texture_parameter_impl<Name>(texture, param);
	}
}

template<auto Texture>
void texture_set_wrap_s(const contexts::basic_texture<Texture>& texture, enums::wraps wraps)
{
	_detail::texture_parameter<enums::texture_parameter_name::wrap_s>(texture, static_cast<GLint>(wraps));
}

template<auto Texture>
void texture_set_wrap_t(const contexts::basic_texture<Texture>& texture, enums::wraps wraps)
{
	_detail::texture_parameter<enums::texture_parameter_name::wrap_t>(texture, static_cast<GLint>(wraps));
}

template<auto Texture>
void texture_set_wrap_r(const contexts::basic_texture<Texture>& texture, enums::wraps wraps)
{
	_detail::texture_parameter<enums::texture_parameter_name::wrap_r>(texture, static_cast<GLint>(wraps));
}

template<auto Texture>
void texture_set_minify_filter(const contexts::basic_texture<Texture>& texture, enums::filters filters)
{
	_detail::texture_parameter<enums::texture_parameter_name::minify_filter>(texture, static_cast<GLint>(filters));
}

template<auto Texture>
void texture_set_magnify_filter(const contexts::basic_texture<Texture>& texture, enums::filters filters)
{
	_detail::texture_parameter<enums::texture_parameter_name::magnify_filter>(texture, static_cast<GLint>(filters));
}

template<auto Texture>
void texture_set_image(
	const contexts::basic_texture<Texture>& texture,
	void_ptr_cst data, 
	::std::size_t width, 
	::std::size_t height,
	enums::internal_format internal_format,
	enums::format format,
	enums::channel_type channel_type,
	size_t mipmap_level = 0)
{
	NGS_EXTERNAL_OPENGL_EXPECT_BIND(texture);
	NGS_EXTERNAL_OPENGL_CHECK(::glTexImage2D(
		static_cast<GLenum>(type_traits::object_t<decltype(texture)>::target),
		static_cast<GLint>(mipmap_level),
		static_cast<GLint>(internal_format),
		static_cast<GLsizei>(width),
		static_cast<GLsizei>(height),
		0,
		static_cast<GLenum>(format),
		static_cast<GLenum>(channel_type),
		data
	));
}

template<auto Texture>
void texture_generate_mipmap(const contexts::basic_texture<Texture>& texture)
{
	NGS_EXTERNAL_OPENGL_EXPECT_BIND(texture);
	NGS_EXTERNAL_OPENGL_CHECK(::glGenerateMipmap(static_cast<GLenum>(type_traits::object_t<decltype(texture)>::target)));
}

template<auto Texture>
void texture_active_slot(const contexts::basic_texture<Texture>& texture,enums::texture_slot slot)
{
	NGS_EXTERNAL_OPENGL_CHECK(::glActiveTexture(static_cast<GLenum>(slot)));
	basic::bind(texture);
}

NGS_LIB_MODULE_END