#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/target.h"
#include "NGS/ngl/base/buffer.h"
#include "NGS/ngl/error.h"

NGL_BEGIN
NGL_TARGET_BEGIN

class NGS_API  BufferTarget : public Target<BufferTarget, buffers::BufferObject> {
	friend class  Target<BufferTarget, buffers::BufferObject>;
	static void _Select(state_type* buffer) { NGL_CHECK(glBindBuffer(static_cast<GLenum>(buffer->target), buffer->GetContext())); }
};


NGS_END
NGL_END
