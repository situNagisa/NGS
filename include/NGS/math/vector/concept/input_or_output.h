#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _V>
concept input_or_output_vector = ::std::ranges::random_access_range<_V>;

NGS_LIB_MODULE_END