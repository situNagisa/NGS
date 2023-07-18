#pragma once

#include "NGS/ngl/vertex/array/base.h"
#include "NGS/ngl/shader/shader.h"

NGL_BEGIN

NGL_TARGET_BEGIN

NGS_HPP_INLINE void VertexArray::_Select(state_type* state) { _NGL_CHECK(glBindVertexArray(state->GetContext())); }

NGS_END

NGL_OBJ_BEGIN


NGS_END

NGL_END
