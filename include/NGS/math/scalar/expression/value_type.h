#pragma once

#include "./concept.h"
#include "./value.h"

NGS_MATH_SCALAR_BEGIN

namespace meta
{
	template<class _Type>
	using scalar_value_t = decltype(value(declval<_Type>()));

}

NGS_MATH_SCALAR_END
