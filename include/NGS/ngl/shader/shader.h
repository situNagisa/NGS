#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/target.h"
#include "NGS/ngl/shader/source.h"
#include "NGS/ngl/base/opengl.h"

NGL_BEGIN
NGL_OBJ_BEGIN
class Shader;
NGS_END
NGL_TARGET_BEGIN

class ShaderProgram : public Target<ShaderProgram, objects::Shader> {
	friend class Target<ShaderProgram, objects::Shader>;
	static void _Select(state_type* state);
};

NGS_END
using uniform_offset_t = GLint;
NGL_OBJ_BEGIN

class Shader : public State {
public:
	Shader(Shader&&) = default;
	Shader() { NGL_CHECK(_context = glCreateProgram()); }
	Shader(size_t count, ...)
		: Shader() {
		va_list uniforms;
		va_start(uniforms, count);
		for (size_t i = 0; i < count; i++)
		{
			auto uniform = va_arg(uniforms, const char*);
			_uniforms.insert({ uniform,-1 });
		}
		va_end(uniforms);
	}
	template<std::convertible_to<const char*>... T>
	Shader(T&&... properties)
		: Shader(sizeof...(properties), std::forward<T>(properties)...)
	{}
	~Shader() {
		if (!_context)return;
		NGL_CHECK(glDeleteProgram(_context));
	}

	void Attach(const _ShaderSource& code) { NGL_CHECK(glAttachShader(_context, code.GetContext())); }
	void Link() {
		NGL_CHECK(glLinkProgram(_context));
#if NGS_BUILD_TYPE == NGS_DEBUG
		//NGL_CHECK(glValidateProgram(_context));
		GLint status = GL_FALSE;
		glGetProgramiv(_context, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			GLint length;
			glGetProgramiv(_context, GL_INFO_LOG_LENGTH, &length);
			NGS_ASSERT(length, "get length fail!");
			std::string info(length, 0);
			glGetProgramInfoLog(_context, length, &length, info.data());
			NGS_ASSERT(false, ngs::Format("link shader fail!\n %s", info.c_str()));
		}

#endif
		for (auto& [uniform, offset] : _uniforms) {
			NGL_CHECK(offset = glGetUniformLocation(_context, uniform.c_str()));
			if (offset == -1) {
				NGS_LOGFL(warning, "uniform %s not found!", uniform.c_str());
			}
		}
	}
	void CompileAndLink(std::string_view vertex, std::string_view fragment, std::string_view geometry = "") {
		VertexShader vs(vertex);
		FragmentShader fs(fragment);
		GeometryShader gs(geometry);

		vs.Compile();
		fs.Compile();

		Attach(vs);
		Attach(fs);

		if (!geometry.empty()) {
			gs.Compile();
			Attach(gs);
		}

		Link();
	}


	uniform_offset_t GetUniformLocation(std::string_view name)const {
		NGS_ASSERT(_uniforms.find(name.data()) != _uniforms.end(), "uniform not found!");
		return _uniforms.at(name.data());
	}
private:
	std::unordered_map<std::string, uniform_offset_t> _uniforms{};
};

NGS_END
NGL_END
