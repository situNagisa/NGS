#pragma once

#include "NGS/base/mpl/defined.h"
#include "NGS/base/mpl/mpl_macro.h"

NGS_BEGIN
NGS_MPL_BEGIN

template<class A, class B>
using promote_t = decltype(A() + B());

NGS_END
NGS_END