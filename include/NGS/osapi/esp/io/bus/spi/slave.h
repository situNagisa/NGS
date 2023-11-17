#pragma once

#include "../defined.h"

NGS_OS_ESP_IO_BUS_BEGIN

inline constexpr int spi_default_speed_hz = 10 * 1000 * 1000;

struct NGS_DLL_API spi_slave : embedded::io::bus::spi::slave
{
	NGS_MPL_ENVIRON(spi_slave);
public:
	virtual ~spi_slave()override;

	virtual bool is_opened() const override;
	virtual bool open(embedded::io::pin_t sclk, embedded::io::pin_t miso, embedded::io::pin_t mosi, embedded::io::pin_t cs) override;
	virtual void close() override;

	virtual size_t read(void_ptr buffer, size_t size) override;
	virtual size_t write(void_ptr_cst buffer, size_t size) override;

	virtual embedded::io::pin_t get_miso() const override;
	virtual embedded::io::pin_t get_mosi() const override;
	virtual embedded::io::pin_t get_sclk() const override;
	virtual embedded::io::pin_t get_cs() const override { return _config.spics_io_num; }

protected:
	spi_slave_interface_config_t _config{};
};



NGS_OS_ESP_IO_BUS_END