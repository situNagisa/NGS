#pragma once

#include "NGS/nda/defined.h"

NDA_BEGIN

struct NGS_API Transform {
public:
	matrix_t GetMatrix()const {
		matrix_t matrix = identity_matrix;
		return mla::translate(position + offset) * mla::rotate(rotation) * mla::scale(scale);
	}
public:
	Point2f position{};

	Point2f scale{ 1.0f,1.0f };
	float32 rotation = 0.0f;
	Point2f offset{ 0.0f,0.0f };
};

NDA_END
