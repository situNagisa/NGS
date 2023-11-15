#pragma once

#include "../base.h"

NGS_CONSOLE_BEGIN

namespace detail
{
	struct console_data_impl
	{
		std::ostream* stream;
	};

	constexpr NGS_HPP_GLOBAL_STATIC std::string_view convert_front(text_color color)
	{
		switch (color)
		{
		case text_color::reset:
			return "\033[0m";
		case text_color::black:
			return "\033[30m";
		case text_color::red:
			return "\033[31m";
		case text_color::green:
			return "\033[32m";
		case text_color::yellow:
			return "\033[33m";
		case text_color::blue:
			return "\033[34m";
		case text_color::magenta:
			return "\033[35m";
		case text_color::cyan:
			return "\033[36m";
		case text_color::white:
			return "\033[37m";
		}
		return "";
	}
	constexpr NGS_HPP_GLOBAL_STATIC std::string_view convert_back(text_color color)
	{
		switch (color)
		{
		case text_color::reset:
			return "\033[0m";
		case text_color::black:
			return "\033[40m";
		case text_color::red:
			return "\033[41m";
		case text_color::green:
			return "\033[42m";
		case text_color::yellow:
			return "\033[43m";
		case text_color::blue:
			return "\033[44m";
		case text_color::magenta:
			return "\033[45m";
		case text_color::cyan:
			return "\033[46m";
		case text_color::white:
			return "\033[47m";
		}
		return "";
	}

}

NGS_HPP_INLINE console::console(int count, ...)
	: _data(new detail::console_data_impl())
{
	auto&& data = *static_cast<detail::console_data_impl*>(_data);
	std::ostream* stream{};

	{
		va_list args;
		va_start(args, count);
		if (count == 1)
		{
			stream = va_arg(args, std::ostream*);
		}
		else
		{
			stream = &std::cout;
		}
	}
	data.stream = stream;
}

NGS_HPP_INLINE console::~console()
{
	delete static_cast<detail::console_data_impl*>(_data);
}

NGS_HPP_INLINE void console::set_text_color(text_color front, text_color back)
{
	auto&& data = *static_cast<detail::console_data_impl*>(_data);
	(*data.stream) << detail::convert_front(front) << detail::convert_back(back);
}

NGS_CONSOLE_END
