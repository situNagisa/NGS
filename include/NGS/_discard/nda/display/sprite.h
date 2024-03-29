﻿#pragma once

#include "NGS/nda/defined.h"
#include "NGS/nda/display/display.h"

NDA_BEGIN

class NGS_DLL_API  Sprite : public DisplayObjectContainer {
public:
	using DisplayObjectContainer::DisplayObjectContainer;
	virtual ~Sprite()override {}

	virtual std::string ToString()const override { return format("%s:[%d]", name.empty() ? "sprite" : name.c_str(), GetNumChildren()); }
};

NDA_END
