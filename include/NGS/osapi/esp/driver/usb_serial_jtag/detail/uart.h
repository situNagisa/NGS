#pragma once

#include "./owning.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct esp_uart : owning_uart
{
	NGS_PP_INJECT(esp_uart);
public:
	
	esp_uart(
		uart_port&& port, 
		::std::size_t rx_buffer_size, 
		::std::size_t tx_buffer_size = 0, 
		::std::size_t queue_size = 0, 
		::QueueHandle_t* uart_queue = nullptr,
		int intr_alloc_flags = {})
		: base_type(::std::move(port))
	{
		
		auto result = ::uart_driver_install(base_type::base().value(), static_cast<int>(rx_buffer_size), static_cast<int>(tx_buffer_size), static_cast<int>(queue_size), uart_queue, intr_alloc_flags);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to install uart");
	}

	void configure(const ::uart_config_t& config) const
	{
		auto result = ::uart_param_config(base_type::base().value(), &config);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to configure uart");
	}

	void set_pins(int tx, int rx, int rts = UART_PIN_NO_CHANGE, int cts = UART_PIN_NO_CHANGE) const
	{
		auto result = ::uart_set_pin(base_type::base().value(), tx, rx, rts, cts);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set uart pins");
	}

	void set_baud_rate(::std::uint32_t baud_rate) const
	{
		auto result = ::uart_set_baudrate(base_type::base().value(), baud_rate);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set uart baudrate");
	}

	auto get_baud_rate() const
	{
		::std::uint32_t baud_rate;
		auto result = ::uart_get_baudrate(base_type::base().value(), &baud_rate);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to get uart baudrate");
		return baud_rate;
	}

	void set_word_length(const ::uart_word_length_t& word_length) const
	{
		auto result = ::uart_set_word_length(base_type::base().value(), word_length);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set uart word length");
	}

	auto get_word_length() const
	{
		::uart_word_length_t word_length;
		auto result = ::uart_get_word_length(base_type::base().value(), &word_length);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to get uart word length");
		return word_length;
	}

	void set_stop_bits(const ::uart_stop_bits_t& stop_bits) const
	{
		auto result = ::uart_set_stop_bits(base_type::base().value(), stop_bits);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set uart stop bits");
	}

	auto get_stop_bits() const
	{
		::uart_stop_bits_t stop_bits;
		auto result = ::uart_get_stop_bits(base_type::base().value(), &stop_bits);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to get uart stop bits");
		return stop_bits;
	}

	void set_parity(const ::uart_parity_t& parity) const
	{
		auto result = ::uart_set_parity(base_type::base().value(), parity);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set uart parity");
	}

	auto get_parity() const
	{
		::uart_parity_t parity;
		auto result = ::uart_get_parity(base_type::base().value(), &parity);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to get uart parity");
		return parity;
	}

	void set_flow_control(const ::uart_hw_flowcontrol_t& flow_control, ::std::uint8_t rx_thresh) const
	{
		auto result = ::uart_set_hw_flow_ctrl(base_type::base().value(), flow_control, rx_thresh);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set uart flow control");
	}

	auto get_flow_control() const
	{
		::uart_hw_flowcontrol_t flow_control;
		auto result = ::uart_get_hw_flow_ctrl(base_type::base().value(), &flow_control);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to get uart flow control");
		return flow_control;
	}

	void set_mode(const ::uart_mode_t& mode) const
	{
		auto result = ::uart_set_mode(base_type::base().value(), mode);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set uart mode");
	}
};

NGS_LIB_MODULE_END