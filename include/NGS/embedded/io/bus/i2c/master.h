#pragma once

#include "./base.h"
#include "./message.h"

NGS_EMBEDDED_IO_BUS_I2C_BEGIN

struct NGS_DLL_API master : basic_i2c
{
	NGS_MPL_ENVIRON(master);
public:

	virtual void set_ack(modes::ack ack) = 0;
	virtual size_t transfer(const message* messages, size_t count) = 0;

	//=============================

	size_t transfer(const message& message) { return transfer(&message, 1); }
	size_t transfer(std::ranges::contiguous_range auto&& messages)
		requires std::convertible_to<std::ranges::range_value_t<decltype(messages)>, message>
	{
		return self_type::transfer(std::ranges::data(messages), std::ranges::size(messages));
	}
	size_t transfer(std::same_as<message> auto&&... messages)
	{
		std::array<message, sizeof...(messages)> msg{ messages... };
		return self_type::transfer(msg);
	}

	virtual size_t write(void_ptr_cst buffer, size_t size) override
	{
		return transfer(message{
			.io = modes::io::write,
			.write_buffer = buffer,
			.size = size,
			});
	}
	virtual size_t read(void_ptr buffer, size_t size) override
	{
		return transfer(message{
				.io = modes::io::read,
				.read_buffer = buffer,
				.size = size,
			});
	}
	virtual size_t write_read(
		void_ptr_cst write_data, size_t write_size,
		void_ptr read_data, size_t read_size
	)
	{
		return transfer(
			message{
				.io = modes::io::write,
				.write_buffer = write_data,
				.size = write_size,
			},
			message{
				.io = modes::io::read,
				.read_buffer = read_data,
				.size = read_size
			}
		);
	}
};

NGS_EMBEDDED_IO_BUS_I2C_END