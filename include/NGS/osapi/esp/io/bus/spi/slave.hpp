#pragma once

#include "./slave.h"

NGS_OS_ESP_IO_BUS_BEGIN

NGS_HPP_INLINE spi_slave::~spi_slave() = default;

NGS_HPP_INLINE bool spi_slave::is_opened() const
{
}

NGS_HPP_INLINE bool spi_slave::open(embedded::io::pin_t sclk, embedded::io::pin_t miso, embedded::io::pin_t mosi,
	embedded::io::pin_t cs)
{
}

NGS_HPP_INLINE void spi_slave::close()
{
}

NGS_HPP_INLINE size_t spi_slave::read(void_ptr buffer, size_t size)
{
}

NGS_HPP_INLINE size_t spi_slave::write(void_ptr_cst buffer, size_t size)
{
}

NGS_HPP_INLINE bool spi_slave::is_selected() const
{
}


NGS_OS_ESP_IO_BUS_END
