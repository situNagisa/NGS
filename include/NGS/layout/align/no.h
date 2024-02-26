#pragma once

#include "./constant.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

inline constexpr struct no_align_t : align_constant<static_cast<::std::size_t>(-1), 1> {} no_align{};

NGS_LIB_MODULE_END