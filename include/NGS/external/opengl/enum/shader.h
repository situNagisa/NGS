﻿#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class NGS_DLL_API shader_type {
	vertex = GL_VERTEX_SHADER,
	fragment = GL_FRAGMENT_SHADER,
	geometry = GL_GEOMETRY_SHADER,
	compute = GL_COMPUTE_SHADER,
	tess_control = GL_TESS_CONTROL_SHADER,
	tess_evaluation = GL_TESS_EVALUATION_SHADER,
};


NGS_LIB_MODULE_END
