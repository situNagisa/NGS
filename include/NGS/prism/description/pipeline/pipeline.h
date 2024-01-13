#pragma once

#include "./input.h"
#include "./assembly.h"
#include "./tesselation.h"
#include "./viewport.h"
#include "./rasterization.h"
#include "./blend.h"
#include "./shader.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct graphic_pipeline
{
	vertex_input input{};
	input_assembly assembly{};
	::std::span<shader> shaders{};
	//
	viewport viewport{};
	rasterization rasterization{};
	blend_state blend{};

};

NGS_LIB_MODULE_END