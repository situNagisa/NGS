#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class pin_t : ::std::size_t
{};

constexpr auto operator ""_pin(unsigned long long int x) { return static_cast<pin_t>(x); }


NGS_LIB_MODULE_END