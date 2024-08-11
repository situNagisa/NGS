#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class address_io
{
	write = 0,
	read = 1,
};

enum class address_width
{
	_7 = 7,
	_10 = 10,
};

template<class T, address_width Width = address_width::_10>
concept address = ::std::unsigned_integral<T> && (bits::algorithm::bit_of<T>() >= ::std::to_underlying(Width));

template<address_width Width, address_io IO>
constexpr auto address_cast(address<Width> auto address)
{
	return (address/* << 1*/) | ::std::to_underlying(IO);
}

NGS_LIB_MODULE_END