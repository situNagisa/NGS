﻿#pragma once

#include "./input_or_output.h"

NGS_LIB_MODULE_BEGIN

template<class _V>
concept scalar_vector = input_or_output_vector<_V> && ::std::is_scalar_v<::std::ranges::range_value_t<_V>>;

NGS_LIB_MODULE_END