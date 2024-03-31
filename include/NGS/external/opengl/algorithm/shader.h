#pragma once

#include "../basic.h"
#include "../context.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

void shader_source(const contexts::basic_glsl& glsl, ::std::span<const ::GLchar* const> code)
{
	NGS_EXTERNAL_OPENGL_CHECK(::glShaderSource(glsl.get_context(), static_cast<::GLsizei>(code.size()), code.data(), nullptr));
}

void shader_source(const contexts::basic_glsl& glsl, const ::GLchar* code) { NGS_LIB_MODULE_NAME::shader_source(glsl, { &code,1 }); }

void shader_compile(const contexts::basic_glsl& glsl)
{
	NGS_EXTERNAL_OPENGL_CHECK(::glCompileShader(glsl.get_context()));
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
	::GLint compile_ok = GL_FALSE;
	NGS_EXTERNAL_OPENGL_CHECK(::glGetShaderiv(glsl.get_context(), GL_COMPILE_STATUS, &compile_ok));
	if (compile_ok == GL_FALSE) {
		::GLint log_length;
		NGS_EXTERNAL_OPENGL_CHECK(::glGetShaderiv(glsl.get_context(), GL_INFO_LOG_LENGTH, &log_length));
		::std::string log{};
		log.resize(log_length);
		NGS_EXTERNAL_OPENGL_CHECK(::glGetShaderInfoLog(glsl.get_context(), log_length, NULL, log.data()));
		NGS_ASSERT(false, fmt::c("compile shader code fail! %s", log.c_str()));
	}
#endif
}

void shader_attach(const contexts::shader& shader, const contexts::basic_glsl& glsl)
{
	NGS_EXTERNAL_OPENGL_CHECK(::glAttachShader(shader.get_context(), glsl.get_context()));
}

void shader_link(const contexts::shader& shader)
{
	NGS_EXTERNAL_OPENGL_CHECK(::glLinkProgram(shader.get_context()));
#if NGS_BUILD_TYPE_IS_DEBUG
	//NGS_EXTERNAL_OPENGL_CHECK(::glValidateProgram(_context));
	::GLint status = GL_FALSE;
	NGS_EXTERNAL_OPENGL_CHECK(::glGetProgramiv(shader.get_context(), GL_LINK_STATUS, &status));
	if (status == GL_FALSE) {
		::GLint length;
		NGS_EXTERNAL_OPENGL_CHECK(glGetProgramiv(shader.get_context(), GL_INFO_LOG_LENGTH, &length));
		NGS_ASSERT(length, "get length fail!");
		::std::string info(length, 0);
		NGS_EXTERNAL_OPENGL_CHECK(glGetProgramInfoLog(shader.get_context(), length, &length, info.data()));
		NGS_ASSERT(false, fmt::c("link shader fail!\n %s", info.c_str()));
	}
#endif
}

::std::ptrdiff_t shader_get_uniform_location(const contexts::shader& shader, ::std::string_view uniform_name)
{
	::std::ptrdiff_t result;
	NGS_EXTERNAL_OPENGL_CHECK(result = ::glGetUniformLocation(shader.get_context(), uniform_name.data()));
	return result;
}

namespace _detail
{
	template<class T>
	concept fundametal_uniform = cpt::naked_same_as<T, ::GLint> || cpt::naked_same_as<T, ::GLuint> || cpt::naked_same_as<T, ::GLfloat>;

	template<class T>
	concept ranged_uniform = ::std::ranges::contiguous_range<T> && fundametal_uniform<::std::ranges::range_value_t<T>> && requires(const T & t) { requires (::std::ranges::size(t) > 0) && (::std::ranges::size(t) < 5); };

	template<class T>
	concept uniform = ranged_uniform<T> || fundametal_uniform<T>;

	template<class T,::std::size_t Size>
	concept sized_range_uniform = ranged_uniform<T> && requires(const T & t) { requires (::std::ranges::size(t) == Size); };

	template<class T, class Expect, ::std::size_t Size>
	concept expect_range_uniform = sized_range_uniform<T,Size> && cpt::naked_same_as<::std::ranges::range_value_t<T>, Expect>;

	template<class T, class Expect, ::std::size_t Size>
	concept expect_uniform = expect_range_uniform<T, Expect, Size> || (expect_range_uniform<T[1], Expect, 1> && Size == 1);

	template<class T,bool IsPlural>
	struct shader_uniform_functor;

	template<expect_uniform<::GLint,1> T> struct shader_uniform_functor<T, false> { inline static auto&& value = ::glUniform1i; };
	template<expect_uniform<::GLint,2> T> struct shader_uniform_functor<T, false> { inline static auto&& value = ::glUniform2i; };
	template<expect_uniform<::GLint,3> T> struct shader_uniform_functor<T, false> { inline static auto&& value = ::glUniform3i; };
	template<expect_uniform<::GLint,4> T> struct shader_uniform_functor<T, false> { inline static auto&& value = ::glUniform4i; };
	template<expect_uniform<::GLuint,1> T> struct shader_uniform_functor<T, false> { inline static auto&& value = ::glUniform1ui; };
	template<expect_uniform<::GLuint,2> T> struct shader_uniform_functor<T, false> { inline static auto&& value = ::glUniform2ui; };
	template<expect_uniform<::GLuint,3> T> struct shader_uniform_functor<T, false> { inline static auto&& value = ::glUniform3ui; };
	template<expect_uniform<::GLuint,4> T> struct shader_uniform_functor<T, false> { inline static auto&& value = ::glUniform4ui; };
	template<expect_uniform<::GLfloat,1> T> struct shader_uniform_functor<T, false> { inline static auto&& value = ::glUniform1f; };
	template<expect_uniform<::GLfloat,2> T> struct shader_uniform_functor<T, false> { inline static auto&& value = ::glUniform2f; };
	template<expect_uniform<::GLfloat,3> T> struct shader_uniform_functor<T, false> { inline static auto&& value = ::glUniform3f; };
	template<expect_uniform<::GLfloat,4> T> struct shader_uniform_functor<T, false> { inline static auto&& value = ::glUniform4f; };

	template<expect_uniform<::GLint, 1> T> struct shader_uniform_functor<T, true> { inline static auto&& value = ::glUniform1iv; };
	template<expect_uniform<::GLint, 2> T> struct shader_uniform_functor<T, true> { inline static auto&& value = ::glUniform2iv; };
	template<expect_uniform<::GLint, 3> T> struct shader_uniform_functor<T, true> { inline static auto&& value = ::glUniform3iv; };
	template<expect_uniform<::GLint, 4> T> struct shader_uniform_functor<T, true> { inline static auto&& value = ::glUniform4iv; };
	template<expect_uniform<::GLuint, 1> T> struct shader_uniform_functor<T, true> { inline static auto&& value = ::glUniform1uiv; };
	template<expect_uniform<::GLuint, 2> T> struct shader_uniform_functor<T, true> { inline static auto&& value = ::glUniform2uiv; };
	template<expect_uniform<::GLuint, 3> T> struct shader_uniform_functor<T, true> { inline static auto&& value = ::glUniform3uiv; };
	template<expect_uniform<::GLuint, 4> T> struct shader_uniform_functor<T, true> { inline static auto&& value = ::glUniform4uiv; };
	template<expect_uniform<::GLfloat, 1> T> struct shader_uniform_functor<T, true> { inline static auto&& value = ::glUniform1fv; };
	template<expect_uniform<::GLfloat, 2> T> struct shader_uniform_functor<T, true> { inline static auto&& value = ::glUniform2fv; };
	template<expect_uniform<::GLfloat, 3> T> struct shader_uniform_functor<T, true> { inline static auto&& value = ::glUniform3fv; };
	template<expect_uniform<::GLfloat, 4> T> struct shader_uniform_functor<T, true> { inline static auto&& value = ::glUniform4fv; };

	decltype(auto) shader_uniform(::std::ptrdiff_t location, const ::std::ranges::contiguous_range auto& data, ::std::ptrdiff_t offset)
		requires (uniform<::std::ranges::range_value_t<decltype(data)>>)
	{
		using value_type = type_traits::naked_t<::std::ranges::range_value_t<decltype(data)>>;
		auto&& gl_uniform = shader_uniform_functor<value_type, true>::value;
		location += offset;
		if constexpr(ranged_uniform<value_type>)
		{
			NGS_EXTERNAL_OPENGL_CHECK(gl_uniform(location, ::std::ranges::size(data), ::std::ranges::data(*::std::ranges::begin(data))));
		}
		else
		{
			NGS_EXTERNAL_OPENGL_CHECK(gl_uniform(location, ::std::ranges::size(data), ::std::ranges::data(data)));
		}
	}

	decltype(auto) shader_uniform(::std::ptrdiff_t location, const ranged_uniform auto& data)
	{
		using value_type = type_traits::naked_t<::std::ranges::range_value_t<decltype(data)>>;

		auto&& gl_uniform = shader_uniform_functor<value_type, false>::value;
		auto begin = ::std::ranges::begin(data);
		if constexpr (sized_range_uniform<value_type, 1>)
		{
			NGS_EXTERNAL_OPENGL_CHECK(gl_uniform(location, begin[0]));
		}
		else if constexpr (sized_range_uniform<value_type, 2>)
		{
			NGS_EXTERNAL_OPENGL_CHECK(gl_uniform(location, begin[0], begin[1]));
		}
		else if constexpr (sized_range_uniform<value_type, 3>)
		{
			NGS_EXTERNAL_OPENGL_CHECK(gl_uniform(location, begin[0], begin[1], begin[2]));
		}
		else if constexpr (sized_range_uniform<value_type, 4>)
		{
			NGS_EXTERNAL_OPENGL_CHECK(gl_uniform(location, begin[0], begin[1], begin[2], begin[3]));
		}
	}
}

void shader_set_uniform(const contexts::shader& shader, ::std::ptrdiff_t location, const ::std::ranges::contiguous_range auto& data, ::std::ptrdiff_t offset = 0)
	requires (_detail::uniform<::std::ranges::range_value_t<decltype(data)>>)
{
	NGS_EXTERNAL_OPENGL_EXPECT_BIND(shader);
	_detail::shader_uniform(location, data, offset);
}

void shader_set_uniform(const contexts::shader& shader, ::std::ptrdiff_t location, const _detail::uniform auto& data)
	requires (_detail::fundametal_uniform<::std::ranges::range_value_t<decltype(data)>>)
{
	NGS_EXTERNAL_OPENGL_EXPECT_BIND(shader);
	_detail::shader_uniform(location, data);
}

NGS_LIB_MODULE_END