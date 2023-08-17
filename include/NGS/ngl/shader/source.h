#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/base/state.h"
#include "NGS/ngl/error.h"

NGL_BEGIN
NGL_OBJ_BEGIN
class NGS_API  _ShaderSource : public State {
public:
	_ShaderSource(ShaderType type, const GLchar* const* sources, size_t count)
		: type(type)
	{
		NGL_CHECK(_context = glCreateShader((GLenum)type));
		NGL_CHECK(glShaderSource(_context, count, sources, nullptr));
	}
	_ShaderSource(ShaderType type, const GLchar* sources)
		: type(type)
	{
		NGL_CHECK(_context = glCreateShader((GLenum)type));
		NGL_CHECK(glShaderSource(_context, 1, &sources, nullptr));
	}

	_ShaderSource(_ShaderSource&&) = default;
	~_ShaderSource()noexcept {
		if (!_context)return;
		NGL_CHECK(glDeleteShader(_context));
	}

	void Compile()const {
		NGL_CHECK(glCompileShader(_context));
#if NGS_BUILD_TYPE == NGS_DEBUG
		GLint compile_ok = GL_FALSE;
		NGL_CHECK(glGetShaderiv(_context, GL_COMPILE_STATUS, &compile_ok));
		if (compile_ok == GL_FALSE) {
			GLint log_length;
			NGL_CHECK(glGetShaderiv(_context, GL_INFO_LOG_LENGTH, &log_length));
			std::string log{};
			log.resize(log_length);
			NGL_CHECK(glGetShaderInfoLog(_context, log_length, NULL, log.data()));
			NGS_ASSERT(false, Format("compile %d shader code fail! %s", type, log.c_str()));
		}
#endif
	}

	const ShaderType type;
};

template<ShaderType _Type>
class NGS_API  ShaderSource : public _ShaderSource {
public:
	ShaderSource(ShaderSource&&) = default;
	ShaderSource(const nchar_ptr_cst* sources, size_t count)
		: _ShaderSource(_Type, sources, count)
	{}
	ShaderSource(std::string_view source)
		: _ShaderSource(_Type, source.data())
	{}
};
using VertexShader = ShaderSource<ShaderType::vertex>;
using FragmentShader = ShaderSource<ShaderType::fragment>;
using GeometryShader = ShaderSource<ShaderType::geometry>;
using ComputeShader = ShaderSource<ShaderType::compute>;
using TessControlShader = ShaderSource<ShaderType::tess_control>;
using TessEvaluationShader = ShaderSource<ShaderType::tess_evaluation>;

NGS_END
NGL_END
