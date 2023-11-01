#pragma once

#include "NGS/dl/display/display.h"

NGS_DL_BEGIN

class NGS_DLL_API Sprite : public DisplayObjectContainer {
public:
	using base_type = DisplayObjectContainer;

	using base_type::base_type;
	virtual ~Sprite()override {}
};

NGS_DL_END
