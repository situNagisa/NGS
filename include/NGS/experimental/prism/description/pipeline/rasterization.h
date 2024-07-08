#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct rasterization
{
	enum class polygon_mode_type
	{
		fill,
		line,
		point,
		fill_rectangle_nv,
	};
	enum class cull_mode_type
	{
		none,
		front,
		back,
	};
	enum class front_face_type
	{
		counter_clockwise,
		clockwise,
	};

	bool depth_clamp_enable = false;
	bool rasterizaer_discard_enable = false;
	polygon_mode_type polygon_mode = polygon_mode_type::fill;
	cull_mode_type cull_mode = cull_mode_type::none;
	front_face_type front_face = front_face_type::counter_clockwise;
	struct
	{
		bool enable = false;
		float constant_factor = 0.0f;
		float clamp = 0.0f;
		float slope_factor = 0.0f;
	}depth_bias{};
	float line_width = 1.0f;
};

NGS_LIB_MODULE_END