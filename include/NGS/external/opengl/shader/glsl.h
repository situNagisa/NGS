#pragma once

#include "../enum.h"
#include "../basic.h"
#include "../error.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct basic_glsl : basic::context
{
	NGS_MPL_ENVIRON(basic_glsl);
private:
	static auto _create(enums::shader_type target)
	{
		context_t context;
		NGS_EXTERNAL_OPENGL_CHECK(context = ::glCreateShader(static_cast<::GLenum>(target)));
		return context;
	}
public:
	basic_glsl(enums::shader_type target) noexcept : base_type(_create(target)) {}
	basic_glsl(self_type&&) = default;
	~basic_glsl()
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteShader(get_context()));
	}

	self_type& operator=(self_type&& other) noexcept
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteShader(get_context()));
		_set_context(0);
		base_type::operator=(::std::move(other));
		return *this;
	}

	void set_code(::std::span<const ::GLchar* const> code)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glShaderSource(get_context(), static_cast<::GLsizei>(code.size()), code.data(), nullptr));
	}
	void set_code(const ::GLchar* code) { set_code({ &code,1 }); }

	void compile()
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glCompileShader(get_context()));
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
		::GLint compile_ok = GL_FALSE;
		NGS_EXTERNAL_OPENGL_CHECK(::glGetShaderiv(get_context(), GL_COMPILE_STATUS, &compile_ok));
		if (compile_ok == GL_FALSE) {
			::GLint log_length;
			NGS_EXTERNAL_OPENGL_CHECK(::glGetShaderiv(get_context(), GL_INFO_LOG_LENGTH, &log_length));
			::std::string log{};
			log.resize(log_length);
			NGS_EXTERNAL_OPENGL_CHECK(::glGetShaderInfoLog(get_context(), log_length, NULL, log.data()));
			NGS_ASSERT(false, fmt::c("compile %d shader code fail! %s", log.c_str()));
		}
#endif
	}
};

template<enums::shader_type Target>
struct glsl : basic_glsl
{
	NGS_MPL_ENVIRON(glsl);
public:
	constexpr static auto target = Target;

	glsl() : base_type(target) {}
	glsl(self_type&&) = default;
	using base_type::operator=;
};



NGS_LIB_MODULE_END