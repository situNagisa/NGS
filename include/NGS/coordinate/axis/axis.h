#pragma once

#include "NGS/coordinate/axis/concept.h"

NGS_COORDINATE_BEGIN

template<int _Sign, size_t _Dimension>
struct axis {
	static constexpr auto sign = _Sign;
	static constexpr size_t dimension = _Dimension;
};

NGS_COORDINATE_END
