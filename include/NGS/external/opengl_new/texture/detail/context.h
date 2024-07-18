#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	auto texture_creator()
	{
		contextes::context_t context;
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glGenTextures(1, &context));
		return context;
	}
	void texture_deleter(contextes::context_t context)
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glDeleteTextures(1, &context));
	}
	template<enums::texture_target Target>
	void texture_binder(contextes::context_t context)
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glBindTexture(::std::to_underlying(Target), context));
	}

	NGS_EXTERNAL_OPENGL_CONTEXT_DEFINE_BASIC_CONTEXT(unknown_texture_context, _detail::texture_creator, _detail::texture_deleter);

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
struct basic_texture : _detail::unknown_texture_context
{
	NGS_PP_INJECT(basic_texture);
public:
	constexpr static auto target = Target;
	using machine_type = contextes::context_machine<self_type, _detail::texture_binder<target>>;

	template<enums::texture_parameter_name Name>
	void _parameter(auto&& param) const
	{
		auto gl_texture_parameter = _detail::texture_get_parameter_functor<decltype(param)>();
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(gl_texture_parameter(::std::to_underlying(target), ::std::to_underlying(Name), NGS_PP_PERFECT_FORWARD(param)));
	}

	void set_wrap_s(enums::wraps wraps) const { _parameter<enums::texture_parameter_name::wrap_s>(static_cast<GLint>(wraps)); }

	void set_wrap_t(enums::wraps wraps) const { _parameter<enums::texture_parameter_name::wrap_t>(static_cast<GLint>(wraps)); }

	void set_wrap_r(enums::wraps wraps) const { _parameter<enums::texture_parameter_name::wrap_r>(static_cast<GLint>(wraps)); }

	void set_minify_filter(enums::filters filters) const { _parameter<enums::texture_parameter_name::minify_filter>(static_cast<GLint>(filters)); }

	void set_magnify_filter(enums::filters filters) const { _parameter<enums::texture_parameter_name::magnify_filter>(static_cast<GLint>(filters)); }

	void set_image(
		const void* data,
		::std::size_t width,
		::std::size_t height,
		enums::texture_internal_format internal_format,
		enums::texture_format format,
		enums::texture_channel_type channel_type,
		size_t mipmap_level = 0) const
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glTexImage2D(
			::std::to_underlying(target),
			static_cast<GLint>(mipmap_level),
			::std::to_underlying(internal_format),
			static_cast<GLsizei>(width),
			static_cast<GLsizei>(height),
			0,
			::std::to_underlying(format),
			::std::to_underlying(channel_type),
			data
		));
	}

	void generate_mipmap() const
	{
		NGS_EXTERNAL_OPENGL_CONTEXT_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glGenerateMipmap(::std::to_underlying(target)));
	}

	void active_slot(enums::texture_slot slot) const
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glActiveTexture(::std::to_underlying(slot)));
		contextes::bind(*this);
	}

};

namespace _detail
{
	template <auto Args>
	void derived_from_texture(const basic_texture<Args>&);
}

template <class T>
concept texture = requires(const T & obj) { _detail::derived_from_texture(obj); };

using texture_1d = basic_texture<enums::texture_target::_1d>;
using texture_1d_array = basic_texture<enums::texture_target::_1d_array>;
using texture_2d = basic_texture<enums::texture_target::_2d>;
using texture_2d_array = basic_texture<enums::texture_target::_2d_array>;
using texture_3d = basic_texture<enums::texture_target::_3d>;
using texture_rectangle = basic_texture<enums::texture_target::rectangle>;

NGS_LIB_MODULE_END