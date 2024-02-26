#pragma once

#include "./constant.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

inline constexpr struct default_align_t : align_constant<0, 0> {} default_align{};


NGS_LIB_MODULE_END