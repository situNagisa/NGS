#pragma once

#include "../enum.h"
#include "../basic.h"
#include "../error.h"
#include "./glsl.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct shader : basic::context
{
	NGS_MPL_ENVIRON(shader);
private:
	static auto _create()
	{
		context_t context;
		NGS_EXTERNAL_OPENGL_CHECK(context = ::glCreateProgram());
		return context;
	}

public:
	struct machine_type : bases::singleton<machine_type>
	{
		using context_type = shader;

		void bind(const context_type& context) const
		{
			NGS_EXTERNAL_OPENGL_CHECK(::glUseProgram(context.get_context()));
		}
	};

	shader() noexcept : base_type(_create()) {}
	shader(self_type&&) = default;
	~shader()
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteProgram(get_context()));
	}

	self_type& operator=(self_type&& other) noexcept
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteProgram(get_context()));
		_set_context(0);
		base_type::operator=(::std::move(other));
		return *this;
	}

	::std::ptrdiff_t get_uniform_location(::std::string_view uniform_name) const
	{
		::std::ptrdiff_t result;
		NGS_EXTERNAL_OPENGL_CHECK(result = ::glGetUniformLocation(get_context(), uniform_name.data()));
		return result;
	}

	void attach(const basic_glsl& glsl)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glAttachShader(get_context(), glsl.get_context()));
	}

	void link()
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glLinkProgram(get_context()));
#if NGS_BUILD_TYPE_IS_DEBUG
		//NGS_EXTERNAL_OPENGL_CHECK(::glValidateProgram(_context));
		::GLint status = GL_FALSE;
		NGS_EXTERNAL_OPENGL_CHECK(::glGetProgramiv(get_context(), GL_LINK_STATUS, &status));
		if (status == GL_FALSE) {
			::GLint length;
			NGS_EXTERNAL_OPENGL_CHECK(glGetProgramiv(get_context(), GL_INFO_LOG_LENGTH, &length));
			NGS_ASSERT(length, "get length fail!");
			::std::string info(length, 0);
			NGS_EXTERNAL_OPENGL_CHECK(glGetProgramInfoLog(get_context(), length, &length, info.data()));
			NGS_ASSERT(false, fmt::c("link shader fail!\n %s", info.c_str()));
		}
#endif
	}
};



NGS_LIB_MODULE_END