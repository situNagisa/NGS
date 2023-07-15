﻿#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/target.h"
#include "NGS/ngl/base/buffer.h"
#include "NGS/ngl/error.h"

NGL_BEGIN
NGL_TARGET_BEGIN

class BufferTarget : public Target<BufferTarget, buffers::Buffer> {
	friend class base;
	void _Select(state_type* buffer) { _NGL_CHECK(glBindBuffer((GLenum)buffer->target, buffer->GetContext())); }
};


NGS_END
NGL_END
