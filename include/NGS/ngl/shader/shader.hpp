#pragma once

#include "NGS/ngl/shader/shader.h"

NGL_BEGIN
NGL_TARGET_BEGIN
NGS_HPP_INLINE void ShaderProgram::_Select(state_type* state) { NGL_CHECK(glUseProgram(state->GetContext())); }
NGS_END


NGL_END
