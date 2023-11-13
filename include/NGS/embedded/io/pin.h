#pragma once

#include "./defined.h"

NGS_EMBEDDED_IO_BEGIN

NGS_DLL_API using pin_t = int;
inline constexpr pin_t invalid_pin = static_cast<pin_t>(-1);

NGS_EMBEDDED_IO_END