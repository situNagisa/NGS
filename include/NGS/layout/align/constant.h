#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using align_t = ::std::size_t;

template<align_t Align>
using align_constant = ccpt::constant_<align_t, Align>;

inline constexpr align_t no_align = static_cast<align_t>(-1);
inline constexpr align_t default_align = 0;

using no_align_t = align_constant<no_align>;
using default_align_t = align_constant<default_align>;

NGS_LIB_MODULE_END
