#pragma once

#include "NGS/math/space/axis/concept.h"

NGS_SPACE_BEGIN

template<size_t _Dimension, int _Sign = 1>
struct axis {
	static constexpr auto sign = _Sign;
	static constexpr size_t dimension = _Dimension;
};

NGS_SPACE_END
