#pragma once

#include "NGS/dl/display/sprite.h"

NGS_DL_BEGIN

class NGS_API Stage final: public Sprite, public DeleteCopy {
public:
	using base_type = Sprite;
	using base_type::base_type;
};

NGS_DL_END
