#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/buffer.h"
#include "NGS/ngl/base/target.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/vertex/indices.h"

NGL_BEGIN

class NGS_DLL_API  IIndicesCtrl {
protected:
	using self_type = IIndicesCtrl;
public:

	virtual buffers::Indices& GetIndices() = 0;
	virtual const buffers::Indices& GetIndices()const = 0;
	virtual void AddSequence(size_t vertex_begin, size_t vertex_count) = 0;
	virtual size_t GetIndicesCount()const = 0;
	virtual void Clear() = 0;
};


NGL_END
