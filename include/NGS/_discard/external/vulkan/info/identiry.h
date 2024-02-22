#pragma once

#include "./environment.h"

NGS_LIB_MODULE_BEGIN

inline constexpr auto identity = [](auto& obj) -> auto& {return obj; };

NGS_LIB_MODULE_END