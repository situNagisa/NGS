#pragma once

#include "NGS/ngl/vertex/indices.h"
#include "NGS/ngl/vertex/ctrl/default.h"

NGL_BEGIN

class NGS_API  PolygonIndicesCtrl : public DefaultIndicesCtrl {
	NGS_MPL_ENVIRON(PolygonIndicesCtrl);
public:
	PolygonIndicesCtrl(size_t vertex_count, Usage usage)
		: DefaultIndicesCtrl(3 * (vertex_count - 2), usage)
	{}
	PolygonIndicesCtrl(PolygonIndicesCtrl&&) = default;

	void AddSequence(size_t vertex_begin, size_t vertex_count)override {
		NGS_ASSERT(vertex_count > 2);
		std::vector<indices_t> indices{};
		for (size_t i = vertex_begin + 1; i < vertex_begin + vertex_count - 1; i++)
		{
			indices.push_back(vertex_begin);
			indices.push_back(i);
			indices.push_back(i + 1);
		}
		_indices.AddIndices(_count, indices);
		_count += indices.size();
	}
};


NGL_END
