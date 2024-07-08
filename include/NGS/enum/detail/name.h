#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<auto Value>
constexpr decltype(auto) enum_name()
{
	constexpr ::std::string_view name = symbols::field_symbol_name<Value>();
	auto start = name.find_last_of("::") + 1;
	return ::std::string_view(name.data() + start, name.size() - start);
}

NGS_LIB_MODULE_END