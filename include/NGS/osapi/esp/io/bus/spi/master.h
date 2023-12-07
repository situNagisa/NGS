#pragma once

#include "../defined.h"
#include "./device.h"
#include "../../../tick_type.h"

NGS_OS_ESP_IO_BUS_BEGIN
inline constexpr spi_host_device_t spi_invalid_host = static_cast<spi_host_device_t>(allocators::invalid_id);

struct NGS_DLL_API spi_master final : embedded::io::spi::master, bases::delete_copy
{
	NGS_MPL_ENVIRON(spi_master);
public:
	constexpr spi_master() = default;
	virtual ~spi_master()override;

	constexpr virtual bool is_opened() const override { return _host != spi_invalid_host; }
	virtual bool open(embedded::io::pin_t sclk, embedded::io::pin_t miso, embedded::io::pin_t mosi) override;
	virtual void close() override;

	constexpr virtual embedded::io::pin_t get_miso() const override { return _config.miso_io_num; }
	constexpr virtual embedded::io::pin_t get_mosi() const override { return _config.mosi_io_num; }
	constexpr virtual embedded::io::pin_t get_sclk() const override { return _config.sclk_io_num; }

	using base_type::write;
	using base_type::read;
	virtual size_t read(void_ptr buffer, size_t size) override;
	virtual size_t write(void_ptr_cst buffer, size_t size) override;

	virtual void select(const embedded::io::spi::device& device) override { return select(spi_device(device)); }
	virtual void add_device(const embedded::io::spi::device& device) override { return add_device(spi_device(device)); }
	virtual void remove_device(const embedded::io::spi::device& device) override { return remove_device(spi_device(device)); }
	virtual const spi_device* get_current_device() const override { return _current_device.has_value() ? &_current_device.value() : nullptr; }

	bool open(const spi_bus_config_t& config);

	void lock();
	void unlock();
	bool is_locking() const { return _is_locking; }

	void select(const spi_device& device);
	void add_device(const spi_device& device);
	void remove_device(const spi_device& device);

	void polling(spi_transaction_t& transaction)const;

	size_t polling(
		void_ptr_cst tx_buffer, void_ptr rx_buffer, size_t size,
		void_ptr user = nullptr, uint32 flags = 0
	) const {
		spi_transaction_t t{};
		t.length = bits::as_bit(size);
		t.tx_buffer = tx_buffer;
		t.rx_buffer = rx_buffer;
		t.user = user;
		t.flags = flags;

		polling(t);

		return t.rxlength;
	}

	struct transaction_type final : spi_transaction_t
	{
		constexpr void set_length(size_t size) { length = bits::as_bit(size); }
		constexpr size_t get_rx_length()const { return bits::as_byte(rxlength); }
		constexpr void set_tx_buffer(void_ptr_cst buffer, size_t size)
		{
			tx_buffer = buffer;
			set_length(size);
		}
		constexpr void set_tx_buffer(::std::ranges::contiguous_range auto&& buffer) {
			transaction_type::set_tx_buffer(::std::ranges::data(buffer), ::std::ranges::size(buffer));
		}
		constexpr void set_tx_data(auto&& buffer)
		{
			if constexpr (sizeof(buffer) <= sizeof(tx_data))
			{
				::std::memcpy(tx_data, &buffer, sizeof(buffer));
				flags |= SPI_TRANS_USE_TXDATA;
				set_length(sizeof(buffer));
			}
			else
			{
				transaction_type::set_tx_buffer(&buffer, sizeof(buffer));
			}
		}
		constexpr void set_rx_buffer(void_ptr buffer, size_t size)
		{
			rx_buffer = buffer;
			set_length(size);
		}
		constexpr void set_rx_buffer(::std::ranges::contiguous_range auto&& buffer) {
			transaction_type::set_rx_buffer(::std::ranges::data(buffer), ::std::ranges::size(buffer));
		}
		constexpr void set_rx_data(auto& buffer)
		{
			if constexpr (sizeof(buffer) <= sizeof(rx_data))
			{
				flags |= SPI_TRANS_USE_RXDATA;
				set_length(sizeof(buffer));
			}
			else
			{
				transaction_type::set_rx_buffer(&buffer, sizeof(buffer));
			}
		}
		constexpr void get_rx_data(auto& buffer)
		{
			NGS_ASSERT(get_rx_length() <= sizeof(rx_data));
			::std::memcpy(&buffer, rx_data, rxlength);
		}
	};

	void polling_transmit(void_ptr_cst tx_buffer, size_t size, void_ptr user = nullptr, uint32 flags = 0)const { polling(tx_buffer, nullptr, size, user, flags); }
	void polling_transmit(auto&& target, void_ptr user = nullptr, uint32 flags = 0)const
	{
		transaction_type t{};
		t.set_tx_data(NGS_PP_PERFECT_FORWARD(target));
		t.user = user;
		t.flags |= flags;

		polling(t);
	}

	size_t polling_receive(void_ptr rx_buffer, size_t size, void_ptr user = nullptr, uint32 flags = 0)const { return polling(nullptr, rx_buffer, size, user, flags); }
	size_t polling_receive(auto& target, void_ptr user = nullptr, uint32 flags = 0)const
	{
		transaction_type t{};
		t.set_rx_data(target);
		t.user = user;
		t.flags |= flags;

		polling(t);

		if constexpr (sizeof(target) <= 4)
			t.get_rx_data(target);

		return t.get_rx_length();
	}

	void queue(spi_transaction_t& transaction, esp_tick_type_t ticks_to_wait = portMAX_DELAY)const;
	spi_transaction_t* wait_queue(esp_tick_type_t ticks_to_wait = portMAX_DELAY)const;

private:
	void _remove_device(embedded::io::pin_t cs);
private:
	spi_host_device_t _host = spi_invalid_host;
	spi_bus_config_t _config = {};
	std::unordered_map<embedded::io::pin_t, spi_device_handle_t> _device_mapper{};
	std::optional<spi_device> _current_device{};
	spi_device_handle_t _current_handle = nullptr;
	bool _is_locking = false;
};

NGS_OS_ESP_IO_BUS_END