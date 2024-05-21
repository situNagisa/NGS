#pragma once

#include "NGS/mpl/defined.h"

NGS_MPL_BEGIN

template<class _Pair>
concept CPair = requires() {
	typename _Pair::first_type;
	typename _Pair::second_type;
};

NGS_MPL_END
