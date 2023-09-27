#pragma once

#include "NGS/math/space/axis/concept.h"

NGS_SPACE_BEGIN

template<int _Sign, size_t _Dimension>
struct axis {
	static constexpr auto sign = _Sign;
	static constexpr size_t dimension = _Dimension;
};

NGS_SPACE_END
