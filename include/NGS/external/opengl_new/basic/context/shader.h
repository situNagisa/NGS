#pragma once

#include "../config.h"
#include "../enum.h"
#include "../error.h"
#include "../reflect.h"
#include "../uniform.h"
#include "./basic.h"
#include "./bind.h"
#include "./glsl.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

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

	void set_uniform(auto&&... args)const
		requires ::std::invocable<decltype(NGS_EXTERNAL_OPENGL_BASIC_UNIFORM_NS::set_uniform),decltype(args)...>
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(*this);
		NGS_EXTERNAL_OPENGL_CHECK(NGS_EXTERNAL_OPENGL_BASIC_UNIFORM_NS::set_uniform(NGS_PP_PERFECT_FORWARD(args)...));
	}
};


NGS_LIB_MODULE_END