#pragma once

#include "NGS/extend/color/defined.h"
#include "NGS/extend/color/concept.h"

NGS_BEGIN
NGS_CONCEPT

template<class _Constant>
concept CColorConstants = requires() {
	{ _Constant::white };
	{ _Constant::black };
	{ _Constant::red };
	{ _Constant::green };
	{ _Constant::blue };
	{ _Constant::cyan };
	{ _Constant::magenta };
	{ _Constant::yellow };
	{ _Constant::transparent };
};

NGS_END
NGS_END
NGS_COLOR_SPACE_BEGIN

template<class>
struct ColorConstants;

NGS_COLOR_SPACE_END