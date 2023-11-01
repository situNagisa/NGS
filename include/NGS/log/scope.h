#pragma once

#include "./defined.h"

NGS_LOG_BEGIN

class NGS_DLL_API scope_holder {
public:
	constexpr scope_holder() = default;
	constexpr ~scope_holder() = default;
};

NGS_LOG_END
