#pragma once

#include "../enum.h"
#include "../error.h"
#include "./basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<enums::glsl_target Target>
	auto glsl_creator()
	{
		context_t context;
		NGS_EXTERNAL_OPENGL_CHECK(context = ::glCreateShader(static_cast<::GLenum>(Target)));
		return context;
	}
	void glsl_deleter(context_t context)
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glDeleteShader(context));
	}
}

template<enums::glsl_target Target>
struct glsl : raii_context<_detail::glsl_creator<Target>,_detail::glsl_deleter>
{
	NGS_PP_INJECT(glsl);
public:
	constexpr static auto target = Target;

	using base_type::base_type;
	using base_type::operator=;

	void source(::std::span<const ::GLchar* const> code) const
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glShaderSource(self_type::get_handle(), static_cast<::GLsizei>(code.size()), code.data(), nullptr));
	}

	void source(const ::GLchar* code)  const { self_type::source({ &code,1 }); }

	void compile() const
	{
		NGS_EXTERNAL_OPENGL_CHECK(::glCompileShader(self_type::get_handle()));
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
		::GLint compile_ok = GL_FALSE;
		NGS_EXTERNAL_OPENGL_CHECK(::glGetShaderiv(self_type::get_handle(), GL_COMPILE_STATUS, &compile_ok));
		if (compile_ok == GL_FALSE) {
			::GLint log_length;
			NGS_EXTERNAL_OPENGL_CHECK(::glGetShaderiv(self_type::get_handle(), GL_INFO_LOG_LENGTH, &log_length));
			::std::string log{};
			log.resize(log_length);
			NGS_EXTERNAL_OPENGL_CHECK(::glGetShaderInfoLog(self_type::get_handle(), log_length, NULL, log.data()));
			NGS_ASSERT(false, fmt::c("compile shader code fail! %s", log.c_str()));
		}
#endif
	}
};


NGS_LIB_MODULE_END