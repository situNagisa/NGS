#pragma once

#include "../../defined.h"

NGS_STATIC_FUNCTIONAL_BEGIN

using index_t = int;

template<index_t _Index>
struct placeholder : std::integral_constant<index_t, _Index>
{
	static_assert(_Index > 0, "invalid placeholder index");
};

NGS_STATIC_FUNCTIONAL_END