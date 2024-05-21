#pragma once

#include "./bit.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept fundamental = 
	::std::unsigned_integral<type_traits::object_t<T>>
	&& !::std::same_as<type_traits::object_t<T>, bool>
	&& !::std::same_as<type_traits::object_t<T>, char>
	&& !::std::same_as<type_traits::object_t<T>, char8_t>
	&& !::std::same_as<type_traits::object_t<T>, char16_t>
	&& !::std::same_as<type_traits::object_t<T>, char32_t>
	&& !::std::same_as<type_traits::object_t<T>, wchar_t>;

template<class T>
concept bit_operatable = requires(const type_traits::object_t<T>& left, const type_traits::object_t<T>& right, int shift)
{
	{ left & right } -> ::std::convertible_to<type_traits::object_t<T>>;
	{ left | right } -> ::std::convertible_to<type_traits::object_t<T>>;
	{ left ^ right } -> ::std::convertible_to<type_traits::object_t<T>>;
	{ ~left } -> ::std::convertible_to<type_traits::object_t<T>>;

	{ left << shift } -> ::std::convertible_to<type_traits::object_t<T>>;
	{ left >> shift } -> ::std::convertible_to<type_traits::object_t<T>>;
};

template<class T>
concept range = ::std::ranges::range<T> && bit<::std::ranges::range_value_t<T>> && bit_operatable<T>;

template<class T>
concept random_access_range = range<T> && ::std::ranges::random_access_range<T>;

template<class T>
concept output_range = range<T> && ::std::ranges::output_range<T, bool>;

NGS_LIB_MODULE_END