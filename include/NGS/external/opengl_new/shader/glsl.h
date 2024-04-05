#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::glsl_target Target>
struct basic_glsl
{
	NGS_MPL_ENVIRON_BEGIN(basic_glsl);
public:
	using code_type = const ::GLchar*;
	using context_type = NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::glsl<Target>;

	basic_glsl() = default;
	explicit(false) basic_glsl(code_type code) : self_type({ &code, 1 }) {}
	explicit(false) basic_glsl(::std::span<const code_type> code)
	{
		_context.source(code);
		_context.compile();
	}

	constexpr auto&& get_context() const { return _context; }

	context_type _context;
};

using vertex_glsl = basic_glsl<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::glsl_target::vertex>;
using fragment_glsl = basic_glsl<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::glsl_target::fragment>;
using geometry_glsl = basic_glsl<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::glsl_target::geometry>;
using compute_glsl = basic_glsl<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::glsl_target::compute>;
using tess_control_glsl = basic_glsl<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::glsl_target::tess_control>;
using tess_evaluation_glsl = basic_glsl<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::glsl_target::tess_evaluation>;

NGS_LIB_MODULE_END