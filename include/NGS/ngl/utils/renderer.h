#pragma once

#include "NGS/ngl/environment/environment.h"
#include "NGS/ngl/environment/shader.h"
#include "NGS/ngl/environment/vertex_array.h"

NGL_BEGIN

class Renderer {
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
		for (auto& environment : environments) {
			environment->Build();
		}

		_shader.Build();
		_vertex_array.Build();

		_vertex_array.Destroy();

		for (auto& environment : environments) {
			environment->Destroy();
		}
	}

	template<std::derived_from<env::IEnvironment> T, class... _Args> requires std::constructible_from<T, _Args...>
	T& AddEnvironment(_Args&&... args) {
		auto environment = std::make_shared<T>(std::forward<_Args>(args)...);
		environments.push_back(environment);
		return *environment;
	}
	template<std::derived_from<env::IEnvironment> T>
	T& AddEnvironment(std::shared_ptr<T>&& shared_ptr) {
		environments.push_back(std::move(shared_ptr));
		return *shared_ptr;
	}
public:
	std::vector<std::shared_ptr<env::IEnvironment>> environments{};
private:
	env::VertexArray _vertex_array{};
	env::Shader _shader{};
};

NGL_END
