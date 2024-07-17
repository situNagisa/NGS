#pragma once

#include "./char.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<enums::shader_category Target>
	auto code_creator()
	{
		contextes::context_t context;
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(context = ::glCreateShader(static_cast<::GLenum>(Target)));
		return context;
	}
	void code_deleter(contextes::context_t context)
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glDeleteShader(context));
	}
}

template<enums::shader_category Target>
struct code : contextes::raii_context<_detail::code_creator<Target>,_detail::code_deleter>
{
	NGS_PP_INJECT(code);
public:
	using char_type = code_char_t;
	constexpr static auto target = Target;

	using base_type::base_type;
	using base_type::operator=;

	void source(::std::basic_string_view<char_type> code) const { self_type::source(code.data()); }

	void source(::std::span<const char_type* const> code) const
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glShaderSource(self_type::get_handle(), static_cast<::GLsizei>(code.size()), code.data(), nullptr));
	}

	void source(const char_type* code)  const { self_type::source({ &code,1 }); }

	void compile() const
	{
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glCompileShader(self_type::get_handle()));
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
		auto compile_ok = GL_FALSE;
		NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glGetShaderiv(self_type::get_handle(), GL_COMPILE_STATUS, &compile_ok));
		if (compile_ok == GL_FALSE) {
			::GLint log_length;
			NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glGetShaderiv(self_type::get_handle(), GL_INFO_LOG_LENGTH, &log_length));
			::std::string log{};
			log.resize(log_length);
			NGS_EXTERNAL_OPENGL_ERROR_CHECK(::glGetShaderInfoLog(self_type::get_handle(), log_length, NULL, log.data()));
			NGS_ASSERT(false, fmt::c("compile shader code fail! %s", log.c_str()));
		}
#endif
	}
};

using vertex_code = code<enums::shader_category::vertex>;
using fragment_code = code<enums::shader_category::fragment>;
using geometry_code = code<enums::shader_category::geometry>;
using compute_code = code<enums::shader_category::compute>;
using tess_control_code = code<enums::shader_category::tess_control>;
using tess_evaluation_code = code<enums::shader_category::tess_evaluation>;

namespace _detail
{
	template <auto Args>
	void derived_from_code(const code<Args>&);
}

template <class T>
concept shader_code = requires(const T & obj) { _detail::derived_from_code(obj); };

template<shader_code Code>
decltype(auto) make_compiled_code(auto&& code)
	requires requires(Code coder) { { coder.source(NGS_PP_PERFECT_FORWARD(code)) }; }
{
	Code result{};
	result.source(NGS_PP_PERFECT_FORWARD(code));
	result.compile();
	return result;
}

NGS_LIB_MODULE_END