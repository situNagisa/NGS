#pragma once

#include "./value.h"

NGS_SYMBOL_ID_BEGIN

template<auto Value>
	requires ::std::is_enum_v<decltype(Value)>
constexpr auto enum_name()
{
	return value_name<Value>();
}

NGS_SYMBOL_ID_END
