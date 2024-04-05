#pragma once

#include "../error.h"
#include "./basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	auto texture_creator()
	{
		context_t context;
		NGS_EXTERNAL_OPENGL_CHECK(::glGenTextures(1, &context));
		return context;
	}
	void texture_deleter(context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteTextures(1, &context));
	}
	template<enums::texture_target Target>
	void texture_binder(context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glBindTexture(static_cast<GLenum>(Target), context));
	}

	NGS_EXTERNAL_OPENGL_DEFINE_BASIC_CONTEXT(unknown_texture, _detail::texture_creator, _detail::texture_deleter);

	template<class Type, bool IsPointer>
	struct texture_parameter_functor;

	template<>
	struct texture_parameter_functor< GLfloat, false> { inline static auto&& value = ::glTexParameterf; };
	template<>
	struct texture_parameter_functor<GLfloat, true> { inline static auto&& value = ::glTexParameterfv; };
	template<>
	struct texture_parameter_functor<GLint, false> { inline static auto&& value = ::glTexParameteri; };
	template<>
	struct texture_parameter_functor<GLint, true> { inline static auto&& value = ::glTexParameteriv; };

	template<class ParameterType>
	auto texture_get_parameter_functor()
	{
		using parameter_type = type_traits::naked_t<ParameterType>;
		using value_type = type_traits::naked_t<::std::remove_pointer_t<parameter_type>>;
		return texture_parameter_functor<value_type, ::std::is_pointer_v<parameter_type>>::value;
	}
}

template<enums::texture_target Target>
struct basic_texture : _detail::unknown_texture
{
	NGS_MPL_ENVIRON(basic_texture);
public:
	constexpr static auto target = Target;
	using machine_type = context_machine<self_type, _detail::texture_binder<target>>;

	template<enums::texture_parameter_name Name>
	void _parameter(auto&& param) const
	{
		auto gl_texture_parameter = _detail::texture_get_parameter_functor<decltype(param)>();
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_CHECK(gl_texture_parameter(static_cast<gl_enum_t>(target), static_cast<gl_enum_t>(Name), NGS_PP_PERFECT_FORWARD(param)));
	}

	void set_wrap_s(enums::wraps wraps) const { _parameter<enums::texture_parameter_name::wrap_s>(static_cast<GLint>(wraps)); }

	void set_wrap_t(enums::wraps wraps) const { _parameter<enums::texture_parameter_name::wrap_t>(static_cast<GLint>(wraps)); }

	void set_wrap_r(enums::wraps wraps) const { _parameter<enums::texture_parameter_name::wrap_r>(static_cast<GLint>(wraps)); }

	void set_minify_filter(enums::filters filters) const { _parameter<enums::texture_parameter_name::minify_filter>(static_cast<GLint>(filters)); }

	void set_magnify_filter(enums::filters filters) const { _parameter<enums::texture_parameter_name::magnify_filter>(static_cast<GLint>(filters)); }

	void set_image(
		void_ptr_cst data,
		::std::size_t width,
		::std::size_t height,
		NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_internal_format internal_format,
		NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_format format,
		NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_channel_type channel_type,
		size_t mipmap_level = 0) const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_CHECK(::glTexImage2D(
			static_cast<GLenum>(target),
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

	void generate_mipmap() const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_CHECK(::glGenerateMipmap(static_cast<GLenum>(target)));
	}

	void active_slot(enums::texture_slot slot) const
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glActiveTexture(static_cast<GLenum>(slot)));
		bind(*this);
	}

};

using texture_1d = basic_texture<enums::texture_target::_1d>;
using texture_1d_array = basic_texture<enums::texture_target::_1d_array>;
using texture_2d = basic_texture<enums::texture_target::_2d>;
using texture_2d_array = basic_texture<enums::texture_target::_2d_array>;
using texture_3d = basic_texture<enums::texture_target::_3d>;
using texture_rectangle = basic_texture<enums::texture_target::rectangle>;

NGS_LIB_MODULE_END