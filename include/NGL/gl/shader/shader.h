#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"

NGL_BEGIN

class ShaderProgram;

class Shader {
public:
	friend class ShaderProgram;

public:
	Shader(const std::string& path, GLenum type);
	~Shader()noexcept;

	operator bool()const { return _id; }
private:

private:
	GLuint _id = 0;
};

struct ShaderProgramDef {
	std::string
		vertex{},
		fragment{}
	;
};

class ShaderProgram {
public:

public:
	ShaderProgram(const ShaderProgramDef& def);
	~ShaderProgram()noexcept;

	void Bind()const noexcept;
	static void Unbind() noexcept;

	void SetUniform1i(const std::string& name, int value)const noexcept;
	void SetUniform1f(const std::string& name, float value)const noexcept;
	void SetUniform2f(const std::string& name, const Point2f& value)const noexcept;
	void SetUniform3f(const std::string& name, const Point3f& value)const noexcept;
	void SetUniform4f(const std::string& name, const Point4f& value)const noexcept;
	void SetUniformMat4f(const std::string& name, const float* value)const noexcept;

	operator bool()const { return _id; }
private:

private:
	GLuint _id = 0;
};


NGL_END
