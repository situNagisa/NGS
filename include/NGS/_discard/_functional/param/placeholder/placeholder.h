#pragma once

#include "./defined.h"
#include "../../index.h"

NGS_LIB_MODULE_BEGIN

template<index_t _Index>
struct placeholder : std::integral_constant<index_t, _Index>
{
	static_assert(_Index > 0, "invalid placeholder index");
};

NGS_LIB_MODULE_END
NGS_LIB_MODULE_EXPORT(placeholder);