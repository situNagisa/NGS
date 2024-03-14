#pragma once

#include "../enum.h"
#include "../context.h"
#include "../algorithm.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<enums::shader_type Target>
struct basic_glsl
{
	NGS_MPL_ENVIRON_BEGIN(basic_glsl);
public:
	using code_type = const ::GLchar*;
	using context_type = contexts::glsl<Target>;

	basic_glsl() = default;
	explicit(false) basic_glsl(code_type code) : self_type({ &code, 1 }) {}
	explicit(false) basic_glsl(::std::span<const code_type> code)
	{
		algorithm::shader_source(_context, code);
		algorithm::shader_compile(_context);
	}

	constexpr auto&& get_context() const { return _context; }

	context_type _context;
};

NGS_LIB_MODULE_END
NGS_LIB_BEGIN

using vertex_glsl = NGS_LIB_MODULE_NAME::basic_glsl<enums::shader_type::vertex>;
using fragment_glsl = NGS_LIB_MODULE_NAME::basic_glsl<enums::shader_type::fragment>;
using geometry_glsl = NGS_LIB_MODULE_NAME::basic_glsl<enums::shader_type::geometry>;
using compute_glsl = NGS_LIB_MODULE_NAME::basic_glsl<enums::shader_type::compute>;
using tess_control_glsl = NGS_LIB_MODULE_NAME::basic_glsl<enums::shader_type::tess_control>;
using tess_evaluation_glsl = NGS_LIB_MODULE_NAME::basic_glsl<enums::shader_type::tess_evaluation>;

NGS_LIB_END