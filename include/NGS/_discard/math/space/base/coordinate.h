#pragma once

#include "NGS/math/space/base/concept.h"

NGS_SPACE_BEGIN

template<CAxis... _Axes>
struct coordinate {
	using axes_type = boost::fusion::vector<_Axes...>;
};

NGS_SPACE_END
