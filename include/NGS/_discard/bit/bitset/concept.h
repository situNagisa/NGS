#pragma once

#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept bit_fundamental = 
	::std::unsigned_integral<type_traits::object_t<T>>
	&& !::std::same_as<type_traits::object_t<T>, bool>
	&& !::std::same_as<type_traits::object_t<T>, char>
	&& !::std::same_as<type_traits::object_t<T>, char8_t>
	&& !::std::same_as<type_traits::object_t<T>, char16_t>
	&& !::std::same_as<type_traits::object_t<T>, char32_t>
	&& !::std::same_as<type_traits::object_t<T>, wchar_t>;

//template<class T>
//concept convertible_to_bit_fundamental = bit_fundamental<underlying_type_t<T>> && ::std::convertible_to<T, underlying_type_t<T>>;

template<class T>
concept bit_array = ::std::is_array_v<type_traits::object_t<T>> && bit_fundamental<::std::ranges::range_value_t<T>>;

template<class T>
concept bitset = bit_fundamental<T> || bit_array<T>;

NGS_LIB_MODULE_END