﻿#pragma once

#include "NGS/ngl/shader/shader.h"

NGL_BEGIN
NGL_TARGET_BEGIN
void ShaderProgram::_Select(state_type* state) { _NGL_CHECK(glUseProgram(state->GetContext())); }
NGS_END


NGL_END
