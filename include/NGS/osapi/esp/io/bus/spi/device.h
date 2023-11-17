#pragma once

#include "../defined.h"

NGS_OS_ESP_IO_BUS_BEGIN

struct NGS_DLL_API spi_device : embedded::io::bus::spi::device, spi_device_interface_config_t
{
	NGS_MPL_ENVIRON(spi_device);
	using config_type = spi_device_interface_config_t;
public:
	using config_type::config_type;

	constexpr spi_device() = default;
	constexpr spi_device(const self_type&) = default;
	constexpr spi_device(const base_type& other)
	{
		spics_io_num = other.get_cs();
		clock_speed_hz = static_cast<decltype(clock_speed_hz)>(other.get_frequency());
		mode = static_cast<int>(other.get_polarity()) << 1 | static_cast<int>(other.get_phase());
	}

	constexpr void set_cs(embedded::io::pin_t cs) { spics_io_num = cs; }
	constexpr virtual embedded::io::pin_t get_cs() const override { return spics_io_num; }
	constexpr virtual embedded::io::frequency_t get_frequency() const override { return clock_speed_hz; }

	constexpr virtual embedded::io::bus::spi::modes::phase get_phase() const override
	{
		return static_cast<embedded::io::bus::spi::modes::phase>(mode & 0x1);
	}
	constexpr void set_phase(embedded::io::bus::spi::modes::phase phase)
	{
		mode = bits::set(mode, bits::scope(0), static_cast<int>(phase));
	}
	constexpr virtual embedded::io::bus::spi::modes::polarity get_polarity() const override
	{
		return static_cast<embedded::io::bus::spi::modes::polarity>((mode >> 1) & 0x1);
	}
	constexpr void set_polarity(embedded::io::bus::spi::modes::polarity polarity)
	{
		mode = bits::set(mode, bits::scope(1), static_cast<int>(polarity));
	}
};

NGS_OS_ESP_IO_BUS_END