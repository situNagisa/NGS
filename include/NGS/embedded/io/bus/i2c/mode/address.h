#pragma once

#include "./defined.h"
#include "./io.h"

NGS_EMBEDDED_IO_BUS_I2C_MODE_BEGIN

using address_t = uint16;

constexpr address_t invalid_address = 0;

enum class NGS_DLL_API address
{
	_7 = 7,
	_10 = 10,
};

constexpr auto write_address(address_t address)
{
	return (address << 1) | static_cast<address_t>(io::write);
}
constexpr auto read_address(address_t address)
{
	return (address << 1) | static_cast<address_t>(io::read);
}

NGS_EMBEDDED_IO_BUS_I2C_MODE_END