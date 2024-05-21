#pragma once

#include "../physical.h"
#include "./port.h"
#include "./defined.h"


NGS_LIB_MODULE_BEGIN

struct char_set
{
	using value_type = ::std::uint16_t;

	const value_type backspace = 0x100;
	const value_type newline = '\n';
};

template<char_set CharSet = {} >
struct console
{
	NGS_PP_INJECT_BEGIN(console);
public:
	using value_type = ::std::uint16_t;

	constexpr static char_set char_set = CharSet;

	constexpr console(
		value_type* cga_memory,
		::std::uint16_t control_port = 0x3d4,
		::std::uint16_t position_port = 0x3d5,
		::std::size_t width = 80,
		::std::size_t height = 25
	)
		: _ports{ control_port, position_port }
		, _width{ width }
		, _height{ height }
		, _cga_memory{ cga_memory }
	{
		//::std::memset(_cga_memory, 0, sizeof(value_type) * _width * _height);
	}

	auto get_cursor_position() const
	{
		value_type position{};

		_ports.control.output(::std::uint8_t{ 14 });
		position = _ports.position.input();
		position <<= bits::algorithm::byte_to_bit(1);
		_ports.control.output(::std::uint8_t{ 15 });
		position |= _ports.position.input();

		return position;
	}
	void set_cursor_position(value_type position) const
	{
		_ports.control.output(::std::uint8_t{ 14 });
		_ports.position.output(static_cast<::std::uint8_t>(position >> bits::algorithm::byte_to_bit(1)));
		_ports.control.output(::std::uint8_t{ 15 });
		_ports.position.output(position);
	}

	[[nodiscard]] ::std::string_view cga_put_char(value_type c) const
	{
		value_type position = get_cursor_position();

		switch (c)
		{
		case char_set.newline:
			position += _width - position % _width;
			break;
		case char_set.backspace:
			if (position > 0) --position;
			break;
		default:
			_cga_memory[position++] = (bits::algorithm::extract(c, 0, bits::algorithm::byte_to_bit(1))) | 0x0700;
			break;
		}

		if (position > 25 * 80)
		{
			return "console buffer overflow";
		}

		//scroll up
		if ((position / _width) >= _height - 1)
		{
			::std::memmove(_cga_memory, _cga_memory + _width, sizeof(value_type) * (_height - 1) * _width);
			position -= _width;
			::std::memset(_cga_memory + position, 0, sizeof(value_type) * (_height * _width - position));
		}

		set_cursor_position(position);

		_cga_memory[position] = ' ' | 0x0700;

		return {};
	}

	

	struct
	{
		port control = 0x3d4;
		port position = 0x3d5;
	}_ports{};
	const ::std::size_t _width = 80;
	const ::std::size_t _height = 25;
	value_type* _cga_memory;
};

NGS_LIB_MODULE_END
