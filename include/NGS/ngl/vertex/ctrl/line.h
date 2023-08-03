#pragma once

#include "NGS/ngl/vertex/indices.h"
#include "NGS/ngl/vertex/ctrl/default.h"

NGL_BEGIN

class LineIndicesCtrl : public DefaultIndicesCtrl {
private:

public:
	LineIndicesCtrl(size_t vertex_count, Usage usage)
		: DefaultIndicesCtrl(2 * vertex_count, usage)
	{}
	LineIndicesCtrl(LineIndicesCtrl&&) = default;

	void AddSequence(size_t vertex_begin, size_t vertex_count)override {
		NGS_ASSERT(vertex_count > 1);
		std::vector<indices_t> indices{};
		for (indices_t i = vertex_begin; i < vertex_begin + vertex_count - 1; ++i) {
			indices.push_back(i);
			indices.push_back(i + 1);
		}
		_indices.AddIndices(_count, indices);
		_count += indices.size();
	}
};


NGL_END
