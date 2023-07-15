#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/context.h"
#include "NGS/ngl/gl/error.h"
#include "NGS/ngl/gl_enum.h"

NGLGL_BEGIN

class _ShaderCode : public Context<GLuint> {
public:
	_ShaderCode(ShaderCodeType type, const char** codes, size_t count)
		: _type(type)
	{
		_NGL_CHECK(_handle = glCreateShader((GLenum)type));
		_NGL_CHECK(glShaderSource(_handle, count, codes, nullptr));
	}
	_ShaderCode(ShaderCodeType type, const char* code)
		: _ShaderCode(type, &code, 1)
	{}
	_ShaderCode(ShaderCodeType type, std::ranges::random_access_range auto&& codes)
		: _ShaderCode(type, std::ranges::cdata(codes))
	{}
	_ShaderCode(_ShaderCode&&) = default;
	~_ShaderCode()noexcept { if (!_handle)return; _NGL_CHECK(glDeleteShader(_handle)); }

	void Compile()const {
		_NGL_CHECK(glCompileShader(_handle));
#if NGS_BUILD_TYPE == NGS_DEBUG
		GLint compile_ok = GL_FALSE;
		_NGL_CHECK(glGetShaderiv(_handle, GL_COMPILE_STATUS, &compile_ok));
		if (compile_ok == GL_FALSE) {
			GLint log_length;
			_NGL_CHECK(glGetShaderiv(_handle, GL_INFO_LOG_LENGTH, &log_length));
			std::string log{};
			log.resize(log_length);
			_NGL_CHECK(glGetShaderInfoLog(_handle, log_length, NULL, log.data()));
			NGS_ASSERT(false, Format("compile %d shader code fail! %s", _type, log.c_str()));
		}
#endif
	}

	ShaderCodeType GetType()const { return _type; }
private:
	ShaderCodeType _type = {};
};
template<ShaderCodeType _Type>
class ShaderCode : public _ShaderCode {
public:
	ShaderCode(const char** codes, size_t length)
		: _ShaderCode(_Type, codes, length)
	{}
	ShaderCode(const char* code)
		: _ShaderCode(_Type, &code, 1)
	{}
	ShaderCode(std::ranges::random_access_range auto&& codes)
		: _ShaderCode(_Type, codes)
	{}
	ShaderCode(ShaderCode&&) = default;
};
using VertexShaderCode = ShaderCode<ShaderCodeType::vertex>;
using FragmentShaderCode = ShaderCode<ShaderCodeType::fragment>;
using GeometryShaderCode = ShaderCode<ShaderCodeType::geometry>;
using ComputeShaderCode = ShaderCode<ShaderCodeType::compute>;
using TessControlShaderCode = ShaderCode<ShaderCodeType::tess_control>;
using TessEvaluationShaderCode = ShaderCode<ShaderCodeType::tess_evaluation>;

_NGL_DECALRE_CONTEXT(Shader, GLuint) {
private:
	static void _GENERATE(handle_type & handle) { handle = glCreateProgram(); }
	static void _DESTROY(handle_type & handle) { glDeleteProgram(handle); }
public:
	_NGL_CONTEXT_DEFAULT_CONSTRUCTOR(Shader);

	void Attach(const _ShaderCode & code) { _NGL_CHECK(glAttachShader(_handle, code.GetHandle())); }
	void Link()const {
		_NGL_CHECK(glLinkProgram(_handle));
#if NGS_BUILD_TYPE == NGS_DEBUG
		//_NGL_CHECK(glValidateProgram(_handle));
		GLint status = GL_FALSE;
		glGetProgramiv(_handle, GL_LINK_STATUS, &status);
		NGS_ASSERT(status != GL_FALSE, "link shader fail!");
#endif
	}

	GLint GetUniformLocation(std::string_view name)const { _NGL_CHECK(GLint loc = glGetUniformLocation(_handle, name.data())); return loc; }
};

_NGL_DECALRE_CURRENT(Shader) {
	_NGL_CURRENT_DEFAULT_CONSTRUCTOR(Shader) { _NGL_CHECK(glUseProgram(context)); }
public:
	void SetUniform(std::string_view name, int value) noexcept { _NGL_CHECK(glUniform1i(_context->GetUniformLocation(name), value)); }
	void SetUniform(std::string_view name, float value) noexcept { _NGL_CHECK(glUniform1f(_context->GetUniformLocation(name), value)); }
	void SetUniform(std::string_view name, float v1, float v2) noexcept { _NGL_CHECK(glUniform2f(_context->GetUniformLocation(name), v1, v2)); }
	void SetUniform(std::string_view name, float v1, float v2, float v3) noexcept { _NGL_CHECK(glUniform3f(_context->GetUniformLocation(name), v1, v2, v3)); }
	void SetUniform(std::string_view name, float v1, float v2, float v3, float v4) noexcept { _NGL_CHECK(glUniform4f(_context->GetUniformLocation(name), v1, v2, v3, v4)); }

	void SetUniform(std::string_view name, float32_ptr_cst value, size_t count) { _NGL_CHECK(glUniform1fv(_context->GetUniformLocation(name), count, value)); }
	void SetUniform(std::string_view name, float64_ptr_cst value, size_t count) { _NGL_CHECK(glUniform1dv(_context->GetUniformLocation(name), count, value)); }
	void SetUniform(std::string_view name, int32_ptr_cst value, size_t count) { _NGL_CHECK(glUniform1iv(_context->GetUniformLocation(name), count, value)); }
	void SetUniform(std::string_view name, uint32_ptr_cst value, size_t count) { _NGL_CHECK(glUniform1uiv(_context->GetUniformLocation(name), count, value)); }

	void SetUniformMatrix(std::string_view name, float32_ptr_cst value) noexcept { _NGL_CHECK(glUniformMatrix4fv(_context->GetUniformLocation(name), 1, GL_FALSE, value)); }
private:

};
_NGL_CURRENT_INSTANCE(shader, Shader);

NGLGL_END
