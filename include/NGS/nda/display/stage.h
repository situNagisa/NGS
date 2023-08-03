#pragma once

#include "NGS/nda/defined.h"
#include "NGS/nda/display/display.h"
#include "NGS/nda/display/sprite.h"

NDA_BEGIN

class Stage : public Sprite, public DeleteCopy {
public:
	using Sprite::Sprite;

	virtual std::string ToString()const override { return Format("%s:[%d]", name.empty() ? "stage" : name.c_str(), GetNumChildren()); }
};

NDA_END
