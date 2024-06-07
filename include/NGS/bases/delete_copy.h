#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

class NGS_DLL_API delete_copy {
public:
	constexpr delete_copy() = default;
	constexpr delete_copy(const delete_copy&) = delete;
	constexpr delete_copy& operator=(const delete_copy&) = delete;
};

NGS_LIB_END