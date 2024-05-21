#pragma once

#include "./has_value.h"

NGS_MPL_OPTIONAL_BEGIN

template<class _T, class _Default>
using value_or = std::conditional_t<has_value<_T>, _T, _Default>;

NGS_MPL_OPTIONAL_END