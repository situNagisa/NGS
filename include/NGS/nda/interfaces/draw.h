#pragma once

#include "NGS/nda/defined.h"
#include "NGS/nda/display/stage.h"

NDA_BEGIN

class NGS_API  IDrawer {
public:
	virtual void Draw(const Stage* stage) = 0;
};

NDA_END
