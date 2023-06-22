#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"
#include "NGL/context.h"

NGLGL_BEGIN


class _ShaderCode : public Context<GLuint> {
public:
	_ShaderCode(GLenum type, const char** codes, size_t length);
	_ShaderCode(GLenum type, const char* code)
		: _ShaderCode(type, &code, 1)
	{}
	_ShaderCode(GLenum type, std::ranges::random_access_range auto codes)
		: _ShaderCode(type, std::ranges::cdata(), std::ranges::size(codes))
	{}
	~_ShaderCode()noexcept;

	void Compile()const;
	void CheckError(GLenum target)const;

	GLenum GetType()const { return _type; }
private:
	GLenum _type = {};
};
template<GLenum _Type>
class ShaderCode : public _ShaderCode {
public:
	ShaderCode(const char** codes, size_t length)
		: _ShaderCode(_Type, codes, length)
	{}
	ShaderCode(const char* code)
		: _ShaderCode(_Type, &code, 1)
	{}
	ShaderCode(std::ranges::random_access_range auto codes)
		: _ShaderCode(_Type, std::ranges::cdata(codes), std::ranges::size(codes))
	{}
};
using VectexShader = ShaderCode<GL_VERTEX_SHADER>;
using FragmentShader = ShaderCode<GL_FRAGMENT_SHADER>;
using GeometryShader = ShaderCode<GL_GEOMETRY_SHADER>;
using ComputeShader = ShaderCode<GL_COMPUTE_SHADER>;
using TessControlShader = ShaderCode<GL_TESS_CONTROL_SHADER>;
using TessEvaluationShader = ShaderCode<GL_TESS_EVALUATION_SHADER>;

class ShaderManager;

_NGL_DECALRE_CONTEXT(Shader, GLuint) {
public:
	ShaderContext();
	~ShaderContext()noexcept;

	void Attach(const _ShaderCode & code);
	void Link()const;

	void CheckError(GLenum target)const;

	GLint GetUniformLocation(std::string_view name)const;
};

_NGL_DECALRE_CURRENT(Shader) {
	_NGL_CURRENT_DEFAULT_CONSTRUCTOR(Shader);
public:
	void SetUniform(std::string_view name, int value) noexcept;
	void SetUniform(std::string_view name, float value) noexcept;
	void SetUniform(std::string_view name, float v1, float v2) noexcept;
	void SetUniform(std::string_view name, float v1, float v2, float v3) noexcept;
	void SetUniform(std::string_view name, float v1, float v2, float v3, float v4) noexcept;
	void SetUniformMatrix(std::string_view name, const float* value) noexcept;
private:

};
_NGL_CURRENT_INSTANCE(shader, Shader);

NGLGL_END
