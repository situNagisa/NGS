#pragma once

#include "./ccpt.h"

NGS_CCPT_BEGIN

NGS_CCPT_VERIFY(constant, constant_<int, 2>);
NGS_CCPT_VERIFY(floating, float_<1.0>);
NGS_CCPT_VERIFY(integral, int_<2>);
NGS_CCPT_VERIFY(uint, uint_<3>);

NGS_CCPT_END