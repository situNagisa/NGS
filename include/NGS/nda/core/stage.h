#pragma once

#include "NGS/nda/core/sprite.h"

NDA_BEGIN

class Stage : public Sprite, public DeleteCopy {
public:
	NGS_TYPE_DEFINE(__stage, this);
public:
	using Sprite::Sprite;
	Stage(__this_right other) = delete;
	__this_ref operator=(__this_right other) = delete;


private:

};

NDA_END
