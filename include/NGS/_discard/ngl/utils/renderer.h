#pragma once

#include "NGS/ngl/environment/environment.h"
#include "NGS/ngl/environment/shader.h"
#include "NGS/ngl/environment/vertex_array.h"

NGL_BEGIN

class NGS_DLL_API  Renderer {
public:

public:
	void SetFlag(const BitSet<8>& flag) { _vertex_array.SetFlag(flag); }
	auto GetFlag() { return _vertex_array.GetFlag(); }

	auto& GetVertexArray() { return _vertex_array.GetVertexArray(); }
	const auto& GetVertexArray()const { return _vertex_array.GetVertexArray(); }
	auto& GetShader() { return _shader.GetShader(); }
	const auto& GetShader()const { return _shader.GetShader(); }

	void SetVertexArray(const std::shared_ptr<objects::VertexArrayBase>& vertex_array) { _vertex_array.SetVertexArray(vertex_array); }
	void SetShader(const std::shared_ptr<objects::Shader>& shader) { _shader.SetShader(shader); }

	void Render() {
		_shader.Build();
		_vertex_array.Build();

		_vertex_array.Destroy();
	}
private:
	env::VertexArray _vertex_array{};
	env::Shader _shader{};
};

NGL_END
