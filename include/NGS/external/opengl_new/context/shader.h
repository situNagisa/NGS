#pragma once

#include "../config.h"
#include "../enum.h"
#include "../error.h"
#include "../reflect.h"
#include "./basic.h"
#include "./bind.h"
#include "./glsl.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept shader_uniform = 
	::std::ranges::contiguous_range<T>
	&& ::std::ranges::contiguous_range<::std::ranges::range_value_t<T>>
	&& reflects::buffer_uniform<::std::ranges::range_value_t<::std::ranges::range_value_t<T>>>
	&& requires(const ::std::ranges::range_value_t<T>&obj) { requires (::std::ranges::size(obj) > 0 && ::std::ranges::size(obj) <= 4); }
;

namespace _detail
{
	auto shader_creator()
	{
		context_t context;
		NGS_EXTERNAL_OPENGL_CHECK(context = ::glCreateProgram());
		return context;
	}
	void shader_deleter(context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteProgram(context));
	}
	void shader_binder(context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glUseProgram(context));
	}
	NGS_EXTERNAL_OPENGL_DEFINE_BINDABLE_CONTEXT(basic_shader, _detail::shader_creator, _detail::shader_deleter, _detail::shader_binder);

	template<class T, class Fundamental, ::std::size_t Dimension>
	concept expect_uniform =
		shader_uniform<T>
		&& requires(const ::std::ranges::range_value_t<T>& obj) { requires (::std::ranges::size(obj) == Dimension); }
		&& cpt::naked_same_as< ::std::ranges::range_value_t<::std::ranges::range_value_t<T>>, Fundamental>;
}

struct shader : _detail::basic_shader
{
	NGS_MPL_ENVIRON(shader);
public:
	using base_type::base_type;
	using base_type::operator=;

	template<auto Target>
	void attach(const glsl<Target>& glsl) const
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glAttachShader(self_type::get_handle(), glsl.get_handle()));
	}

	void link() const
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glLinkProgram(self_type::get_handle()));
#if NGS_BUILD_TYPE_IS_DEBUG
		//NGS_EXTERNAL_OPENGL_CHECK(::glValidateProgram(_context));
		::GLint status = GL_FALSE;
		NGS_EXTERNAL_OPENGL_CHECK(::glGetProgramiv(self_type::get_handle(), GL_LINK_STATUS, &status));
		if (status == GL_FALSE) {
			::GLint length;
			NGS_EXTERNAL_OPENGL_CHECK(glGetProgramiv(self_type::get_handle(), GL_INFO_LOG_LENGTH, &length));
			NGS_ASSERT(length, "get length fail!");
			::std::string info(length, 0);
			NGS_EXTERNAL_OPENGL_CHECK(glGetProgramInfoLog(self_type::get_handle(), length, &length, info.data()));
			NGS_ASSERT(false, fmt::c("link shader fail!\n %s", info.c_str()));
		}
#endif
	}

	::std::ptrdiff_t get_uniform_location(::std::string_view uniform_name) const
	{
		::std::ptrdiff_t result;
		NGS_EXTERNAL_OPENGL_CHECK(result = ::glGetUniformLocation(self_type::get_handle(), uniform_name.data()));
		return result;
	}

	void _set_uniform(::std::ptrdiff_t location,const auto& functor,auto... args)const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_CHECK(functor(static_cast<GLint>(location),args...));
	}
	void set_uniform(::std::ptrdiff_t location, ::std::int32_t value) const { self_type::_set_uniform(location, ::glUniform1i, value); }
	void set_uniform(::std::ptrdiff_t location, ::std::uint32_t value) const { self_type::_set_uniform(location, ::glUniform1ui, value); }
	void set_uniform(::std::ptrdiff_t location, float value) const { self_type::_set_uniform(location, ::glUniform1f, value); }

	void set_uniform(::std::ptrdiff_t location, ::std::int32_t value1, ::std::int32_t value2) const { self_type::_set_uniform(location, ::glUniform2i, value1, value2); }
	void set_uniform(::std::ptrdiff_t location, ::std::uint32_t value1, ::std::uint32_t value2) const { self_type::_set_uniform(location, ::glUniform2ui, value1, value2); }
	void set_uniform(::std::ptrdiff_t location, float value1, float value2) const { self_type::_set_uniform(location, ::glUniform2f, value1, value2); }

	void set_uniform(::std::ptrdiff_t location, ::std::int32_t value1, ::std::int32_t value2, ::std::int32_t value3) const { self_type::_set_uniform(location, ::glUniform3i, value1, value2, value3); }
	void set_uniform(::std::ptrdiff_t location, ::std::uint32_t value1, ::std::uint32_t value2, ::std::uint32_t value3) const { self_type::_set_uniform(location, ::glUniform3ui, value1, value2, value3); }
	void set_uniform(::std::ptrdiff_t location, float value1, float value2, float value3) const { self_type::_set_uniform(location, ::glUniform3f, value1, value2, value3); }

	void set_uniform(::std::ptrdiff_t location, ::std::int32_t value1, ::std::int32_t value2, ::std::int32_t value3, ::std::int32_t value4) const { self_type::_set_uniform(location, ::glUniform4i, value1, value2, value3, value4); }
	void set_uniform(::std::ptrdiff_t location, ::std::uint32_t value1, ::std::uint32_t value2, ::std::uint32_t value3, ::std::uint32_t value4) const { self_type::_set_uniform(location, ::glUniform4ui, value1, value2, value3, value4); }
	void set_uniform(::std::ptrdiff_t location, float value1, float value2, float value3, float value4) const { self_type::_set_uniform(location, ::glUniform4f, value1, value2, value3, value4); }

	void _set_uniform(::std::ptrdiff_t location, auto&& functor, const ::std::ranges::contiguous_range auto& data) const
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_CHECK(functor(location, ::std::ranges::size(data), ::std::ranges::data(data)));
	}

	void set_uniform(::std::ptrdiff_t location, const _detail::expect_uniform<::std::int32_t, 1> auto& data) const{ self_type::_set_uniform(location, ::glUniform1iv, data); }
	void set_uniform(::std::ptrdiff_t location, const _detail::expect_uniform<::std::int32_t, 2> auto& data) const{ self_type::_set_uniform(location, ::glUniform2iv, data); }
	void set_uniform(::std::ptrdiff_t location, const _detail::expect_uniform<::std::int32_t, 3> auto& data) const{ self_type::_set_uniform(location, ::glUniform3iv, data); }
	void set_uniform(::std::ptrdiff_t location, const _detail::expect_uniform<::std::int32_t, 4> auto& data) const{ self_type::_set_uniform(location, ::glUniform4iv, data); }
	void set_uniform(::std::ptrdiff_t location, const _detail::expect_uniform<::std::uint32_t, 1> auto& data) const { self_type::_set_uniform(location, ::glUniform1uiv, data); }
	void set_uniform(::std::ptrdiff_t location, const _detail::expect_uniform<::std::uint32_t, 2> auto& data) const { self_type::_set_uniform(location, ::glUniform2uiv, data); }
	void set_uniform(::std::ptrdiff_t location, const _detail::expect_uniform<::std::uint32_t, 3> auto& data) const { self_type::_set_uniform(location, ::glUniform3uiv, data); }
	void set_uniform(::std::ptrdiff_t location, const _detail::expect_uniform<::std::uint32_t, 4> auto& data) const { self_type::_set_uniform(location, ::glUniform4uiv, data); }
	void set_uniform(::std::ptrdiff_t location, const _detail::expect_uniform<float, 1> auto& data) const { self_type::_set_uniform(location, ::glUniform1fv, data); }
	void set_uniform(::std::ptrdiff_t location, const _detail::expect_uniform<float, 2> auto& data) const { self_type::_set_uniform(location, ::glUniform2fv, data); }
	void set_uniform(::std::ptrdiff_t location, const _detail::expect_uniform<float, 3> auto& data) const { self_type::_set_uniform(location, ::glUniform3fv, data); }
	void set_uniform(::std::ptrdiff_t location, const _detail::expect_uniform<float, 4> auto& data) const { self_type::_set_uniform(location, ::glUniform4fv, data); }

	void set_uniform(::std::ptrdiff_t location, const ::std::ranges::contiguous_range auto& data) const
		requires reflects::buffer_uniform<::std::ranges::range_value_t<decltype(data)>>
	{
		self_type::set_uniform(location, ::std::span<type_traits::object_t<decltype(data)>, 1>{&data, 1});
	}
};


NGS_LIB_MODULE_END