#pragma once

#include "./detail.h"

NGS_LIB_BEGIN

template<class T>
constexpr decltype(auto) field_symbol_name()
{
	return details::symbol_name<T>();
}

template<auto Value>
constexpr decltype(auto) field_symbol_name()
{
	return details::symbol_name<Value>();
}

NGS_LIB_END