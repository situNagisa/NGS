#pragma once
#include "NGS/nda/core/display_object.h"

NDA_BEGIN

class Sprite : public DisplayObjectContainer {
public:
	using DisplayObjectContainer::DisplayObjectContainer;

	virtual __number Width()const override { return 0; }
	virtual __number Height()const override { return 0; }
};

NDA_END
