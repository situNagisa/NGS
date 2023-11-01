#pragma once

#include "./defined.h"

NGS_SYMBOL_ID_BEGIN

template<auto value>
constexpr auto value_name()
{
	constexpr std::string_view name = NGS_PP_PRETTY_FUNCTION_NAME;
#if NGS_COMPILER_IS_CLANG
	auto start = name.find("value = ") + 8; // 8 is length of "value = "
	auto end = name.find_last_of(']');
	return std::string_view{ name.data() + start, end - start };

#elif NGS_COMPILER_IS_GCC
	auto start = name.find("value = ") + 8; // 8 is length of "value = "
	auto end = name.find_last_of(']');
	return std::string_view{ name.data() + start, end - start };

#elif NGS_COMPILER_IS_MSVC
	auto start = name.find("value_name<") + 11; // 11 is length of "value_name<"
	auto end = name.find_last_of('>');
	return std::string_view{ name.data() + start, end - start };
#endif
}

NGS_SYMBOL_ID_END
