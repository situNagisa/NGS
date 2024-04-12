#pragma once

#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept bit_integral = 
	::std::unsigned_integral<T>
	&& !::std::same_as<T, bool>
	&& !::std::same_as<T, char>
	&& !::std::same_as<T, char8_t>
	&& !::std::same_as<T, char16_t>
	&& !::std::same_as<T, char32_t>
	&& !::std::same_as<T, wchar_t>;

template<class T>
concept bitset = bit_integral<underlying_type_t<T>> && ::std::convertible_to<T, underlying_type_t<T>>;

NGS_LIB_MODULE_END