#pragma once

#include "./master.h"
#include "./device.h"

NGS_OS_ESP_IO_BUS_BEGIN

NGS_HPP_INLINE allocators::id<SPI_HOST_MAX> spi_hosts{};

NGS_HPP_INLINE spi_master::~spi_master() = default;

NGS_HPP_INLINE bool spi_master::open(embedded::io::pin_t sclk, embedded::io::pin_t miso, embedded::io::pin_t mosi)
{
	_config.sclk_io_num = sclk;
	_config.miso_io_num = miso;
	_config.mosi_io_num = mosi;
	_config.max_transfer_sz = 0x2000;

	return open(_config);
}

NGS_HPP_INLINE void spi_master::close()
{
	for (auto&& handle : _device_mapper | std::views::values)
	{
		NGS_OS_ESP_ASSERT_ERROR(::spi_bus_remove_device(handle));
	}
	_device_mapper.clear();

	::spi_bus_free(_host);
	spi_hosts.free(_host);
	_host = spi_invalid_host;
}

NGS_HPP_INLINE size_t spi_master::read(void_ptr buffer, size_t size)
{
	spi_transaction_t t{};
	t.length = bits::as_bit(size);
	t.rx_buffer = buffer;
	t.flags = SPI_TRANS_CS_KEEP_ACTIVE;
	polling_transmit(t);

	return bits::as_byte(t.rxlength);
}

NGS_HPP_INLINE size_t spi_master::write(void_ptr_cst buffer, size_t size)
{
	spi_transaction_t t{};
	t.length = bits::as_bit(size);
	t.tx_buffer = buffer;
	t.flags = SPI_TRANS_CS_KEEP_ACTIVE;

	polling_transmit(t);

	return size;
}

NGS_HPP_INLINE bool spi_master::open(const spi_bus_config_t& config)
{
	constexpr auto allocate_host = []-> spi_host_device_t
		{
			auto host = spi_hosts.allocate();
			if (host == allocators::invalid_id)
				NGS_LOGFL(warn, "host allocated fail!");
			return static_cast<spi_host_device_t>(host);
		};

	_config = config;

	while (true)
	{
		_host = allocate_host();
		if (_host == spi_invalid_host)
			return false;
		if (NGS_OS_ESP_EXPECT_ERROR(::spi_bus_initialize(_host, &_config, SPI_DMA_CH_AUTO), format("bus host[%d] already initialized!", _host)))
		{
			NGS_LOGFL(info, "allocate spi host[%d] successfully!", _host);
			break;
		}
	}

	return true;
}

NGS_HPP_INLINE void spi_master::lock()
{
	NGS_OS_ESP_ASSERT_ERROR(::spi_device_acquire_bus(_current_handle, portMAX_DELAY), format("handle = %p", _current_handle));
	_is_locking = true;
}

NGS_HPP_INLINE void spi_master::unlock()
{
	::spi_device_release_bus(_current_handle);
	_is_locking = false;
}

NGS_HPP_INLINE void spi_master::select(const spi_device& device)
{
	_current_device = device;
	_current_handle = _device_mapper.at(device.get_cs());
}

NGS_HPP_INLINE void spi_master::add_device(const spi_device& device)
{
	spi_device_handle_t handle;
	NGS_OS_ESP_ASSERT_ERROR(::spi_bus_add_device(_host, &device, &handle));

	_device_mapper.insert({ device.get_cs(), handle });
}

NGS_HPP_INLINE void spi_master::remove_device(const spi_device& device)
{
	_remove_device(device.get_cs());
}

NGS_HPP_INLINE void spi_master::polling(spi_transaction_t& transaction) const
{
	//NGS_LOGFL(debug, "tx = %p,rx = %p,flag = 0x%08x,size = %d", transaction.tx_buffer, transaction.rx_buffer, transaction.flags, transaction.length);

	NGS_OS_ESP_ASSERT_ERROR(::spi_device_polling_transmit(_current_handle, &transaction), format(
		"handle = %p",
		_current_handle
	));
}

NGS_HPP_INLINE spi_transaction_t* spi_master::wait_queue(esp_tick_type_t ticks_to_wait) const
{
	spi_transaction_t* ts = nullptr;
	NGS_OS_ESP_ASSERT_ERROR(::spi_device_get_trans_result(_current_handle, &ts, ticks_to_wait), format("handle = %p", _current_handle));

	return ts;
}

NGS_HPP_INLINE void spi_master::queue(spi_transaction_t& transaction, esp_tick_type_t ticks_to_wait) const
{
	NGS_OS_ESP_ASSERT_ERROR(::spi_device_queue_trans(_current_handle, &transaction, ticks_to_wait), format("handle = %p", _current_handle));
}

NGS_HPP_INLINE void spi_master::_remove_device(embedded::io::pin_t cs)
{
	if (_current_device && cs == _current_device.value().get_cs())
	{
		_current_device.reset();
		_current_handle = nullptr;
	}
	NGS_OS_ESP_ASSERT_ERROR(::spi_bus_remove_device(_device_mapper.at(cs)), format("handle = %p", _current_handle));
	_device_mapper.erase(cs);
}


NGS_OS_ESP_IO_BUS_END
