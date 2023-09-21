#pragma once

#include "NGS/ngl/environment/environment.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/error.h"
#include "NGS/ngl/vertex/array/base.h"

NGL_ENV_BEGIN

class NGS_API  VertexArray final : public IEnvironment {
public:
	NGS_FLAG(flag_clear, 0);
public:
	VertexArray() = default;
	VertexArray(const std::shared_ptr<objects::VertexArrayBase>& vertex_array) :_vertex_array(vertex_array) {}

	void SetVertexArray(const std::shared_ptr<objects::VertexArrayBase>& vertex_array) { _vertex_array = vertex_array; }
	auto& GetVertexArray() { return _vertex_array; }
	const auto& GetVertexArray()const { return _vertex_array; }

	void SetFlag(const BitSet<8>& flag) { _flag = flag; }
	auto GetFlag()const { return _flag; }

	virtual void Build() override {
		_vertex_array->Update();
		_vertex_array->Render();
	}
	virtual void Destroy() override {
		if (_flag[0])
			_vertex_array->Clear();
	}

private:
	std::shared_ptr<objects::VertexArrayBase> _vertex_array = nullptr;
	BitSet<8> _flag{};
};

NGL_ENV_END
