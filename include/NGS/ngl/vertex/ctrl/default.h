#pragma once

#include "NGS/ngl/vertex/indices.h"
#include "NGS/ngl/vertex/interface/IIndicesCtrl.h"

NGL_BEGIN

class _DefaultIndicesCtrl : public IIndicesCtrl {
public:
	_DefaultIndicesCtrl(size_t vertex_count, Usage usage)
		: _indices(vertex_count, usage)
	{}
	_DefaultIndicesCtrl(_DefaultIndicesCtrl&&) = default;

	buffers::Indices& GetIndices()override { return _indices; }
	const buffers::Indices& GetIndices()const override { return _indices; }

	size_t GetIndicesCount()const override { return _count; }

	virtual void Clear()override { _count = 0; }
protected:
	buffers::Indices _indices;
	size_t _count = 0;
};


NGL_END
