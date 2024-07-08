#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
constexpr auto symbol_name()
{
	constexpr ::std::string_view name = NGS_PP_GET_CURRENT_FUNCTION_PRETTY_NAME();
#if defined(NGS_COMPILER_IS_CLANG)
	auto start = name.find("T = ") + 4; // 4 is length of "T = "
	auto end = name.find_last_of(']');
	return std::string_view{ name.data() + start, end - start };

#elif defined(NGS_COMPILER_IS_GCC)
	auto start = name.find("T = ") + 4; // 4 is length of "T = "
	auto end = name.find_last_of(']');
	return std::string_view{ name.data() + start, end - start };

#elif defined(NGS_COMPILER_IS_MSVC)
	auto start = name.find("symbol_name<") + 12;
	auto end = name.find_last_of('>');
	return ::std::string_view{ name.data() + start, end - start };
#endif
}


template<auto Value>
constexpr auto symbol_name()
{
	constexpr std::string_view name = NGS_PP_GET_CURRENT_FUNCTION_PRETTY_NAME();
#if defined(NGS_COMPILER_IS_CLANG)
	auto start = name.find("Value = ") + 8; // 8 is length of "value = "
	auto end = name.find_last_of(']');
	return std::string_view{ name.data() + start, end - start };

#elif defined(NGS_COMPILER_IS_GCC)
	auto start = name.find("Value = ") + 8; // 8 is length of "value = "
	auto end = name.find_last_of(']');
	return std::string_view{ name.data() + start, end - start };

#elif defined(NGS_COMPILER_IS_MSVC)
	auto start = name.find("symbol_name<") + 12;
	auto end = name.find_last_of('>');
	return std::string_view{ name.data() + start, end - start };
#endif
}


NGS_LIB_MODULE_END