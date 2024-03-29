﻿#pragma once

#include "./defined.h"

NGS_BASES_BEGIN

class NGS_DLL_API delete_copy {
public:
	delete_copy() = default;
	delete_copy(const delete_copy&) = delete;
	delete_copy& operator=(const delete_copy&) = delete;
};

NGS_BASES_END