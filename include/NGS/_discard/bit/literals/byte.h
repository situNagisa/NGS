#pragma once

#include "./defined.h"


NGS_LIB_MODULE_BEGIN

constexpr auto operator ""_b(unsigned long long int x) { return x * (1ull << 0); }

constexpr auto operator ""_kb(unsigned long long int x) { return x * (1ull << 10); }

constexpr auto operator ""_mb(unsigned long long int x) { return x * (1ull << 20); }

constexpr auto operator ""_gb(unsigned long long int x) { return x * (1ull << 30); }

constexpr auto operator ""_tb(unsigned long long int x) { return x * (1ull << 40); }

constexpr auto operator ""_pb(unsigned long long int x) { return x * (1ull << 50); }

NGS_LIB_MODULE_END
