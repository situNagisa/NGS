#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/vertex/array/base.h"
#include "NGS/ngl/shader/shader.h"

NGL_BEGIN

class Renderer {
public:
	NGS_FLAG(flag_clear, 0);

public:

	auto& GetVertexArray() { return _vertex_array; }
	const auto& GetVertexArray()const { return _vertex_array; }
	auto& GetShader() { return _shader; }
	const auto& GetShader()const { return _shader; }

	void SetVertexArray(const std::shared_ptr<objects::VertexArrayBase>& vertex_array) { _vertex_array = vertex_array; }
	void SetShader(const std::shared_ptr<objects::Shader>& shader) { _shader = shader; }

	void Enable(Capabilities c) { _capabilities.insert(c); }
	void Disable(Capabilities c) { _capabilities.erase(c); }
	bool IsEnabled(Capabilities c)const { return _capabilities.find(c) != _capabilities.end(); }

	void Viewport(const Rectanglei& viewport) { _viewport = viewport; }

	void SetBackgroundColor(ARGB32 argb) { _background_color = argb; }
	auto GetBackgroundColor()const { return _background_color; }

	void SetClearBitfield(GLbitfield bitfield) { _clear_bitfield = bitfield; }
	auto GetClearBitfield()const { return _clear_bitfield; }

	void Render() {
		for (auto c : _capabilities) {
			NGL_CHECK(glEnable((GLenum)c));
		}

		if (_viewport.Area()) {
			NGL_CHECK(glViewport(_viewport.x, _viewport.y, _viewport.width, _viewport.height));
		}

		if (_clear_bitfield) {
			NGL_CHECK(glClear(_clear_bitfield));
		}

		NGL_CHECK(glClearColor(
			ARGB32::R::Percent(_background_color.Red()),
			ARGB32::G::Percent(_background_color.Green()),
			ARGB32::B::Percent(_background_color.Blue()),
			ARGB32::A::Percent(_background_color.Alpha())
		));

		if (_shader) {
			_shader->Update();
			OpenGL::I().shader->Select(*_shader);
		}
		if (_vertex_array) {
			_vertex_array->Update();
			_vertex_array->Render();
			if (_flag[0])
				_vertex_array->Clear();
		}

		for (auto c : _capabilities) {
			NGL_CHECK(glDisable((GLenum)c));
		}
	}

private:
	std::shared_ptr<objects::VertexArrayBase> _vertex_array = nullptr;
	std::shared_ptr<objects::Shader> _shader = nullptr;

	Rectanglei _viewport{};
	std::unordered_set<Capabilities> _capabilities{};
	ARGB32 _background_color{};
	GLbitfield _clear_bitfield = 0;

	BitSet<8> _flag = flag_clear;
};

NGL_END
