#pragma once

#include "NGS/math/vector.h"
#include "NGS/math/util.h"

NGS_BEGIN

struct NGS_DLL_API Rotation
{
	Rotation() = default;
	Rotation(float angle)
		: sin(sinf(angle))
		, cos(cosf(angle))
	{}

	void Set(float angle) {
		sin = sinf(angle);
		cos = cosf(angle);
	}

	void SetIdentity() {
		sin = 0.0f;
		cos = 1.0f;
	}

	float GetAngle() const { return atan2f(sin, cos); }

	/// Get the x-axis
	Vector2D<float> GetXAxis() const { return { cos,sin }; }

	/// Get the u-axis
	Vector2D<float> GetYAxis() const { return { -sin, cos }; }

	/// Sine and cosine
	float sin, cos;
};

NGS_END
