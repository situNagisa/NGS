#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<class _T>
concept is_param = cpt::any<_T>;

NGS_LIB_END