#pragma once

#include "./defined.h"

NGS_SYMBOL_ID_BEGIN

template<typename T>
constexpr auto type_name()
{
	constexpr std::string_view name = NGS_PP_PRETTY_FUNCTION_NAME;
#if NGS_COMPILER_IS_CLANG
	auto start = name.find("T = ") + 4; // 4 is length of "T = "
	auto end = name.find_last_of(']');
	return std::string_view{ name.data() + start, end - start };

#elif NGS_COMPILER_IS_GCC
	auto start = name.find("T = ") + 4; // 4 is length of "T = "
	auto end = name.find_last_of(']');
	return std::string_view{ name.data() + start, end - start };

#elif NGS_COMPILER_IS_MSVC
	auto start = name.find("type_name<") + 10; // 10 is length of "type_name<"
	auto end = name.find_last_of('>');
	return std::string_view{ name.data() + start, end - start };
#endif
}

NGS_SYMBOL_ID_END
