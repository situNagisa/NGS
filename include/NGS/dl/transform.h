#pragma once

#include "NGS/dl/defined.h"

NGS_DL_BEGIN

struct NGS_API Transform {
public:
	matrix_type GetMatrix()const;
public:
	point_type position{};

	point_type scale{ 1.0f,1.0f };
	arithmetic_type rotation = 0.0f;
	point_type offset{ 0.0f,0.0f };
};

NGS_DL_END
