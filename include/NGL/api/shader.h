#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"
#include "NGL/gl/gl.h"

NGL_BEGIN

class Shader {
public:

public:
	Shader(std::string_view vertex, std::string_view fragment)
		: Shader(vertex, fragment, "")
	{}
	Shader(std::string_view vertex, std::string_view fragment, std::string_view geometry)
		: _context(gl::shader.Create())
	{
		using gl::ShaderCodeType;

		Active();

		if (!vertex.empty())_context.Attach(gl::ShaderCode<ShaderCodeType::vertex>(vertex));
		if (!fragment.empty())_context.Attach(gl::ShaderCode<ShaderCodeType::fragment>(fragment));
		if (!geometry.empty())_context.Attach(gl::ShaderCode<ShaderCodeType::geometry>(geometry));

		_context.Link();

		Deactivate();
	}
	~Shader() = default;

	void Active() { gl::shader.PushContext(_context); }
	void Deactivate() { gl::shader.PopContext(); }

	void SetUniform(std::string_view name, int value) { NGS_ASSERT(gl::shader.GetContext() == &_context); gl::shader.SetUniform(name, value); }
	void SetUniform(std::string_view name, float value) { NGS_ASSERT(gl::shader.GetContext() == &_context); gl::shader.SetUniform(name, value); }
	void SetUniform(std::string_view name, float32_ptr_cst value, size_t count) { NGS_ASSERT(gl::shader.GetContext() == &_context); gl::shader.SetUniform(name, value, count); }
	void SetUniform(std::string_view name, float64_ptr_cst value, size_t count) { NGS_ASSERT(gl::shader.GetContext() == &_context); gl::shader.SetUniform(name, value, count); }
	void SetUniform(std::string_view name, int32_ptr_cst value, size_t count) { NGS_ASSERT(gl::shader.GetContext() == &_context); gl::shader.SetUniform(name, value, count); }
	void SetUniform(std::string_view name, uint32_ptr_cst value, size_t count) { NGS_ASSERT(gl::shader.GetContext() == &_context); gl::shader.SetUniform(name, value, count); }
private:
	gl::ShaderContext _context = {};
};

NGL_END
