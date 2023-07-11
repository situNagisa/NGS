#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"
#include "NGL/context.h"
#include "NGL/gl/error.h"

NGLGL_BEGIN

enum class ShaderCodeType {
	vertex = GL_VERTEX_SHADER,
	fragment = GL_FRAGMENT_SHADER,
	geometry = GL_GEOMETRY_SHADER,
	compute = GL_COMPUTE_SHADER,
	tess_control = GL_TESS_CONTROL_SHADER,
	tess_evaluation = GL_TESS_EVALUATION_SHADER,
};

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
	~_ShaderCode()noexcept { _NGL_CHECK(glDeleteShader(_handle)); }

	void Compile()const { _NGL_CHECK(glCompileShader(_handle)); }

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
};
using VertexShaderCode = ShaderCode<ShaderCodeType::vertex>;
using FragmentShaderCode = ShaderCode<ShaderCodeType::fragment>;
using GeometryShaderCode = ShaderCode<ShaderCodeType::geometry>;
using ComputeShaderCode = ShaderCode<ShaderCodeType::compute>;
using TessControlShaderCode = ShaderCode<ShaderCodeType::tess_control>;
using TessEvaluationShaderCode = ShaderCode<ShaderCodeType::tess_evaluation>;

_NGL_DECALRE_CONTEXT(Shader, GLuint) {
public:
	ShaderContext() { _NGL_CHECK(_handle = glCreateProgram()); }
	~ShaderContext()noexcept { _NGL_CHECK(glDeleteProgram(_handle)); }

	void Attach(const _ShaderCode & code) { _NGL_CHECK(glAttachShader(_handle, code.GetHandle())); }
	void Link()const {
		_NGL_CHECK(glLinkProgram(_handle));
		_NGL_CHECK(glValidateProgram(_handle));
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
