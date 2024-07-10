#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class NGS_DLL_API capability : gl_enum_t {
	blend = GL_BLEND,
	clip_distance0 = GL_CLIP_DISTANCE0,
	clip_distance1 = GL_CLIP_DISTANCE1,
	clip_distance2 = GL_CLIP_DISTANCE2,
	clip_distance3 = GL_CLIP_DISTANCE3,
	clip_distance4 = GL_CLIP_DISTANCE4,
	clip_distance5 = GL_CLIP_DISTANCE5,
	clip_distance6 = GL_CLIP_DISTANCE6,
	clip_distance7 = GL_CLIP_DISTANCE7,
	color_logic_op = GL_COLOR_LOGIC_OP,
	cull_face = GL_CULL_FACE,
	debug_output = GL_DEBUG_OUTPUT,
	debug_output_synchronous = GL_DEBUG_OUTPUT_SYNCHRONOUS,
	depth_clamp = GL_DEPTH_CLAMP,
	depth_test = GL_DEPTH_TEST,
	dither = GL_DITHER,
	framebuffer_srgb = GL_FRAMEBUFFER_SRGB,
	line_smooth = GL_LINE_SMOOTH,
	multi_sample = GL_MULTISAMPLE,
	polygon_offset_fill = GL_POLYGON_OFFSET_FILL,
	polygon_offset_line = GL_POLYGON_OFFSET_LINE,
	polygon_offset_point = GL_POLYGON_OFFSET_POINT,
	polygon_smooth = GL_POLYGON_SMOOTH,
	primitive_restart = GL_PRIMITIVE_RESTART,
	primitive_restart_fixed_index = GL_PRIMITIVE_RESTART_FIXED_INDEX,
	rasterizer_discard = GL_RASTERIZER_DISCARD,
	sample_alpha_to_coverage = GL_SAMPLE_ALPHA_TO_COVERAGE,
	sample_alpha_to_one = GL_SAMPLE_ALPHA_TO_ONE,
	sample_coverage = GL_SAMPLE_COVERAGE,
	sample_shading = GL_SAMPLE_SHADING,
	sample_mask = GL_SAMPLE_MASK,
	scissor_test = GL_SCISSOR_TEST,
	stencil_test = GL_STENCIL_TEST,
	texture_cube_map_seamless = GL_TEXTURE_CUBE_MAP_SEAMLESS,
	program_point_size = GL_PROGRAM_POINT_SIZE,
};

NGS_LIB_MODULE_END
