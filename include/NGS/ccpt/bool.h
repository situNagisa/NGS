#pragma once

#include "./defined.h"
#include "./fundamental.h"

NGS_CCPT_BEGIN

template<class _T>
concept true_ = boolean<_T> && requires{requires _T::value; };

template<class _T>
concept false_ = boolean<_T> && requires{requires !_T::value; };

NGS_CCPT_END