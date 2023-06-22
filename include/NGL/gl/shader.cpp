#include "NGL/gl/shader.h"
#include "NGL/opengl.h"

NGLGL_BEGIN

_ShaderCode::_ShaderCode(GLenum type, const char** codes, size_t count)
	: _type(type)
{
	_handle = glCreateShader(type);
	glShaderSource(_handle, count, codes, nullptr);
}

_ShaderCode::~_ShaderCode() noexcept
{
	glDeleteShader(_handle);
	_handle = 0;
}

void _ShaderCode::Compile() const
{
	glCompileShader(_handle);
	CheckError(GL_COMPILE_STATUS);
}

void _ShaderCode::CheckError(GLenum target) const
{
	GLint ret = GL_FALSE;
	glGetShaderiv(_handle, target, &ret);
	if (ret)return;
	GLint len = 0;
	glGetShaderiv(_handle, GL_INFO_LOG_LENGTH, &len);
	std::string log;
	log.resize(len);
	glGetShaderInfoLog(_handle, len, nullptr, log.data());
	glDeleteShader(_handle);
	NGS_LOGL(error, log);
}

ShaderContext::ShaderContext() { _handle = glCreateProgram(); }
ShaderContext::~ShaderContext() noexcept {
	glDeleteProgram(_handle);
	_handle = 0;
}
void ShaderContext::Attach(const _ShaderCode& code) { glAttachShader(_handle, code.GetHandle()); }
void ShaderContext::Link() const {
	glLinkProgram(_handle);
	CheckError(GL_LINK_STATUS);
}
void ShaderContext::CheckError(GLenum target) const
{
	GLint ret = GL_FALSE;
	glGetProgramiv(_handle, target, &ret);
	if (ret)return;
	GLint len = 0;
	glGetProgramiv(_handle, GL_INFO_LOG_LENGTH, &len);
	std::string log;
	log.resize(len);
	glGetProgramInfoLog(_handle, len, nullptr, log.data());
	NGS_LOGL(error, log);
}
GLint ShaderContext::GetUniformLocation(std::string_view name) const
{
	GLint loc = glGetUniformLocation(_handle, name.data());
	if (loc < 0) {
		NGS_LOGFL(error, "uniform not found %s", name.data());
		return 0;
	}
	return loc;
}


void Shader::_SET_CURRENT_CONTEXT(context_type::handle_type context) { glUseProgram(context); }

void Shader::SetUniform(std::string_view name, int value) noexcept { glUniform1i(_context->GetUniformLocation(name), value); }
void Shader::SetUniform(std::string_view name, float value) noexcept { glUniform1f(_context->GetUniformLocation(name), value); }
void Shader::SetUniform(std::string_view name, float v1, float v2) noexcept { glUniform2f(_context->GetUniformLocation(name), v1, v2); }
void Shader::SetUniform(std::string_view name, float v1, float v2, float v3) noexcept { glUniform3f(_context->GetUniformLocation(name), v1, v2, v3); }
void Shader::SetUniform(std::string_view name, float v1, float v2, float v3, float v4) noexcept { glUniform4f(_context->GetUniformLocation(name), v1, v2, v3, v4); }
void Shader::SetUniformMatrix(std::string_view name, const float* value) noexcept { glUniformMatrix4fv(_context->GetUniformLocation(name), 1, GL_FALSE, value); }


NGLGL_END

