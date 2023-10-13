#pragma once

#include "./is_align.h"

NGS_LAYOUT_BEGIN

template<class _Align, size_t _DefaultAlign = 1>
concept CAlign = ccpt::UInt<_Align> && is_align(_Align::value, _DefaultAlign);

using no_align_t = ccpt::uint_<no_align>;
using default_align_t = ccpt::uint_<default_align>;

NGS_LAYOUT_END
