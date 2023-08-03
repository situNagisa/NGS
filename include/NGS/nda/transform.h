#pragma once

#include "NGS/nda/defined.h"

NDA_BEGIN

struct Transform {
public:

	

public:
	Point2f position{};

	Point2f scale{ 1.0f,1.0f };
	float32 rotation = 0.0f;
	Point2f offset{ 0.0f,0.0f };
};

NDA_END
