#include "NGL/gl/shader/shader.h"
#include "NGL/opengl.h"

NGL_BEGIN

Shader::Shader(const std::string& path, GLenum type)
{
	_id = glCreateShader(type);
	const char* source[] = { path.c_str() };
	glShaderSource(_id, 1, source, nullptr);
	glCompileShader(_id);
	GLint ret = GL_FALSE;
	glGetShaderiv(_id, GL_COMPILE_STATUS, &ret);
	if (ret == GL_FALSE) {
		GLint len = 0;
		glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &len);
		std::string log;
		log.resize(len);
		glGetShaderInfoLog(_id, len, nullptr, log.data());
		glDeleteShader(_id);
		NGS_Assert(false, log.c_str());
	}
}

Shader::~Shader() noexcept
{
	glDeleteShader(_id);
	_id = 0;
}



ShaderProgram::ShaderProgram(const ShaderProgramDef& def)
{
	_id = glCreateProgram();
	{
		if (!def.vertex.empty()) {
			auto vertex = Shader(def.vertex, GL_VERTEX_SHADER);
			if (!vertex) goto err;
			glAttachShader(_id, vertex._id);
		}

		if (!def.fragment.empty()) {
			auto fragment = Shader(def.fragment, GL_FRAGMENT_SHADER);
			if (!fragment) goto err;
			glAttachShader(_id, fragment._id);
		}
	}
	glBindFragDataLocation(_id, 0, "color");
	glLinkProgram(_id);

	{
		GLint status = GL_FALSE;
		glGetProgramiv(_id, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			GLint len = 0;
			glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &len);
			std::string log;
			log.resize(len);
			glGetProgramInfoLog(_id, len, nullptr, log.data());
			NGS_LOGL(error, log);
			goto err;
		}
	}

	NGS_LOGL(debug, "compile shader program");

	return;
err:;
	glDeleteProgram(_id);
	NGS_Assert(false, "compile shader program failed");
}

ShaderProgram::~ShaderProgram() noexcept
{
	glDeleteProgram(_id);
	_id = 0;
}

void ShaderProgram::Bind() const noexcept
{
	glUseProgram(_id);
}

void ShaderProgram::Unbind() noexcept
{
	glUseProgram(0);
}


NGL_END