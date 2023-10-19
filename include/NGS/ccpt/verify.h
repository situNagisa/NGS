#pragma once

#include "./ccpt.h"

NGS_CCPT_BEGIN

NGS_CCPT_VERIFY(Constant, constant<int, 2>);
NGS_CCPT_VERIFY(Float, float_<1.0>);
NGS_CCPT_VERIFY(Int, int_<2>);
NGS_CCPT_VERIFY(UInt, uint_<3>);

NGS_CCPT_END