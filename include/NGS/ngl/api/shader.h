﻿#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/gl/gl.h"

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
	bool IsActive()const { return gl::shader.GetContext() == &_context; }
	void Deactivate() { gl::shader.PopContext(); }

	void SetUniform(std::string_view name, int value) { NGS_ASSERT(IsActive()); gl::shader.SetUniform(name, value); }
	void SetUniform(std::string_view name, float value) { NGS_ASSERT(IsActive()); gl::shader.SetUniform(name, value); }
	void SetUniform(std::string_view name, float32_ptr_cst value, size_t count) { NGS_ASSERT(IsActive()); gl::shader.SetUniform(name, value, count); }
	void SetUniform(std::string_view name, float64_ptr_cst value, size_t count) { NGS_ASSERT(IsActive()); gl::shader.SetUniform(name, value, count); }
	void SetUniform(std::string_view name, int32_ptr_cst value, size_t count) { NGS_ASSERT(IsActive()); gl::shader.SetUniform(name, value, count); }
	void SetUniform(std::string_view name, uint32_ptr_cst value, size_t count) { NGS_ASSERT(IsActive()); gl::shader.SetUniform(name, value, count); }
	void SetUniform(std::string_view name, const std::ranges::random_access_range auto& values) { NGS_ASSERT(IsActive()); gl::shader.SetUniform(name, std::ranges::cdata(values), std::ranges::size(values)); }

	const auto& GetContext()const { return _context; }
private:
	gl::ShaderContext _context = {};
};

NGL_END