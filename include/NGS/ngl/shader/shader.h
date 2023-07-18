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
	friend class base;
	static void _Select(state_type* state);
};

NGS_END

NGL_OBJ_BEGIN

using uniform_offset_t = GLint;

class Shader : public State {
public:
	Shader(Shader&&) = default;
	Shader() { _NGL_CHECK(_context = glCreateProgram()); }
	Shader(size_t count, ...)
		: Shader() {
		va_list uniforms;
		va_start(uniforms, count);
		for (size_t i = 0; i < count; i++)
		{
			uniform_offset_t offset;
			auto uniform = va_arg(uniforms, const char*);
			_NGL_CHECK(offset = glGetUniformLocation(_context, uniform));
			_uniforms.insert({ uniform,offset });
		}
		va_end(uniforms);
	}
	~Shader() {
		if (!_context)return;
		_NGL_CHECK(glDeleteProgram(_context));
	}

	void Attach(const _ShaderSource& code) { _NGL_CHECK(glAttachShader(_context, code.GetContext())); }
	void Link()const {
		_NGL_CHECK(glLinkProgram(_context));
#if NGS_BUILD_TYPE == NGS_DEBUG
		//_NGL_CHECK(glValidateProgram(_context));
		GLint status = GL_FALSE;
		glGetProgramiv(_context, GL_LINK_STATUS, &status);
		NGS_ASSERT(status != GL_FALSE, "link shader fail!");
#endif
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
