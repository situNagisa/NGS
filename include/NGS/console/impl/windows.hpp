#pragma once

#include "../base.h"

#include <windows.h>

NGS_CONSOLE_BEGIN

namespace detail
{
struct console_data_impl
{
	HANDLE handle{};
};

NGS_HPP_GLOBAL_STATIC WORD convert_front(text_color color)
{
	switch (color)
	{
	case text_color::black:
		return 0;
	case text_color::blue:
		return FOREGROUND_BLUE;
	case text_color::green:
		return FOREGROUND_GREEN;
	case text_color::cyan:
		return FOREGROUND_GREEN | FOREGROUND_BLUE;
	case text_color::red:
		return FOREGROUND_RED;
	case text_color::magenta:
		return FOREGROUND_RED | FOREGROUND_BLUE;
	case text_color::yellow:
		return FOREGROUND_RED | FOREGROUND_GREEN;
	default:
		//[[fallthrough]]
	case text_color::reset:
		//[[fallthrough]]
	case text_color::white:
		return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	}
}
NGS_HPP_GLOBAL_STATIC WORD convert_back(text_color color)
{
	return convert_front(color) << 4;
}

NGS_HPP_GLOBAL_STATIC WORD convert(text_color front, text_color back)
{
	return convert_front(front) | (convert_back(back));
}

}

NGS_HPP_INLINE console::console(int count, ...)
	: _data(new detail::console_data_impl())
{
	auto&& data = *static_cast<detail::console_data_impl*>(_data);
	DWORD stream{};

	{
		va_list args;
		va_start(args, count);
		if (count == 1)
		{
#if NGS_COMPILER_IS_MSVC
#	pragma warning(push)
#	pragma warning(disable: 6269)
#	pragma warning(push)
#	pragma warning(disable: 6011)
#	pragma warning(push)
#	pragma warning(disable: 26451)
#endif
			va_arg(stream, DWORD);
#if NGS_COMPILER_IS_MSVC
#	pragma warning(pop)
#	pragma warning(pop)
#	pragma warning(pop)
#endif
		}
		else
		{
			stream = STD_OUTPUT_HANDLE;
		}
	}
	data.handle = GetStdHandle(stream);
}

NGS_HPP_INLINE console::~console()
{
	delete static_cast<detail::console_data_impl*>(_data);
}

NGS_HPP_INLINE void console::set_text_color(text_color front, text_color back)
{
	auto&& data = *static_cast<detail::console_data_impl*>(_data);
	SetConsoleTextAttribute(data.handle, detail::convert(front, back));
}

NGS_CONSOLE_END
