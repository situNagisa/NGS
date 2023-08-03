#pragma once

#include "NGS/ngl/vertex/indices.h"
#include "NGS/ngl/vertex/ctrl/default.h"

NGL_BEGIN

class VertexIndicesCtrl : public DefaultIndicesCtrl {
private:

public:
	VertexIndicesCtrl(size_t vertex_count, Usage usage)
		: DefaultIndicesCtrl(vertex_count, usage)
	{}
	VertexIndicesCtrl(VertexIndicesCtrl&&) = default;

	void AddSequence(size_t vertex_begin, size_t count)override {
		std::vector<indices_t> indices{};

		for (size_t i = vertex_begin; i < vertex_begin + count; i++)
			indices.push_back(i);

		_indices.AddIndices(_count, indices);
		_count += count;
	}
};


NGL_END
