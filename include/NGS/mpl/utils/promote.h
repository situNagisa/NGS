#pragma once

#include "NGS/mpl/defined.h"

NGS_MPL_BEGIN

NGS_mfunction(promote, class _Left, class _Right) {
	NGS_mcst_t result_type = decltype(_Left() + _Right());
};

template<class _Left, class _Right>
using promote_t = typename promote<_Left, _Right>::result_type;

NGS_MPL_END
