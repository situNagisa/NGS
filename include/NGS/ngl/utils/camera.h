#pragma once

#include "NGS/ngl/defined.h"

NGL_BEGIN

class Camera2D {
public:
	Camera2D(float32 width, float32 height) : size(width, height) {}

	std::array<float32, 3 * 3> GetMatrix3()const {
		auto zoom_size = size / zoom;
		Point2f scale = Point2f{ 2, -2 } / zoom_size;
		Point2f translate = -2 * (center * Point2f{ 1,-1 }) / zoom_size;
		return {
			scale.x,			0,				0,
			0,					scale.y,		0,
			translate.x,		translate.y,	1,
		};
	}
	std::array<float32, 4 * 4> GetMatrix4()const {
		auto zoom_size = size / zoom;
		Point2f scale = Point2f{ 2, -2 } / zoom_size;
		Point2f translate = -2 * (center * Point2f{ 1,-1 }) / zoom_size;
		return {
			scale.x,			0,				0,			0,
			0,					scale.y,		0,			0,
			0,					0,				1,			0,
			translate.x,		translate.y,	0,			1,
		};
	}
public:
	Point2f size;
	Point2f center{};
	float32 zoom = 1.0f;
};

NGL_END
