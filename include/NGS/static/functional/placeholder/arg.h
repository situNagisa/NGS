#pragma once

#include "../defined.h"

NGS_FUNCTIONAL_BEGIN

using arg_index_t = int;

template<arg_index_t _Index>
struct arg : std::integral_constant<arg_index_t, _Index>
{
	static_assert(_Index > 0, "invalid placeholder index");
};

NGS_FUNCTIONAL_END