#pragma once

#include "NGS/dl/display/display.h"
#include "NGS/dl/display/shape/graphic.h"

NGS_DL_BEGIN

class NGS_API Shape : public DisplayObject {
public:
	Shape();

	const std::unique_ptr<IGraphic> graphic;
};



NGS_DL_END
