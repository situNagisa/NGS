#pragma once

#include "./owning.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct command_active_guard : bases::delete_copy
{
	command_active_guard(::i2c_cmd_handle_t handle)
		: _handle(handle)
	{
		auto result = ::i2c_master_start(_handle);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to start I2C command");
	}
	~command_active_guard()
	{
		auto result = ::i2c_master_stop(_handle);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to stop I2C command");
	}

	void write(::std::span<const ::std::uint8_t> bytes, bool ack_enable) const
	{
		auto result = ::i2c_master_write(_handle, bytes.data(), bytes.size(), ack_enable);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to write to I2C command");
	}
	void write_byte(::std::uint8_t byte, bool ack_enable) const
	{
		auto result = ::i2c_master_write_byte(_handle, byte, ack_enable);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to write byte to I2C command");
	}

	void read(::std::span<::std::uint8_t> bytes, ios::iics::ack ack) const
	{
		auto result = ::i2c_master_read(_handle, bytes.data(), bytes.size(), static_cast<::i2c_ack_type_t>(ack));
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to read from I2C command");
	}
	void read_byte(::std::uint8_t& byte, ios::iics::ack ack) const
	{
		auto result = ::i2c_master_read_byte(_handle, &byte, static_cast<::i2c_ack_type_t>(ack));
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to read byte from I2C command");
	}

	::i2c_cmd_handle_t _handle;
};

struct command_link : bases::delete_copy
{
	command_link()
		: _handle(::i2c_cmd_link_create())
	{
		NGS_OSAPI_ESP_CHECK_ASSERT_THROW_MESSAGE(_handle, "Failed to create I2C command link");
	}
	~command_link()
	{
		::i2c_cmd_link_delete(_handle);
	}

	auto start() const
	{
		return command_active_guard(_handle);
	}

	constexpr auto handle() const noexcept { return _handle; }

	::i2c_cmd_handle_t _handle;
};

struct static_command_link : bases::delete_copy
{
	static_command_link(::std::span<::std::uint8_t> command_memory)
		: _handle(::i2c_cmd_link_create_static(command_memory.data(), command_memory.size()))
	{
		NGS_OSAPI_ESP_CHECK_ASSERT_THROW_MESSAGE(_handle, "Failed to create I2C static command link");
	}
	~static_command_link()
	{
		::i2c_cmd_link_delete_static(_handle);
	}

	auto start() const
	{
		return command_active_guard(_handle);
	}

	::i2c_cmd_handle_t _handle;
};



NGS_LIB_MODULE_END