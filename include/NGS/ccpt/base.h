#pragma once

#include "./defined.h"

NGS_CCPT_BEGIN

template<class... _T>
concept none = false;

template<class... _T>
concept any = true;

NGS_CCPT_END
