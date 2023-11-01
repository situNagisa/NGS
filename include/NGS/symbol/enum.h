#pragma once

#include "./value.h"

NGS_SYMBOL_ID_BEGIN

template<auto value>
constexpr auto enum_name()
{
	return value_name<value>();
}

NGS_SYMBOL_ID_END
