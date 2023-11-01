#pragma once

#include "NGS/extend/console.h"

#if NGS_SYSTEM == NGS_SYSTEM_WINDOWS

#include <windows.h>

#endif

NGS_BEGIN

namespace {
inline bool _s_set_text_color = [] {
	Debugger::set_text_color = Console::SetTextColor;
	return true;
	}();
}

#if NGS_SYSTEM == NGS_SYSTEM_WINDOWS

#if true

NGS_HPP_INLINE void Console::SetTextColor(TextColor color) {
	static constexpr byte
		BLACK = 0,
		BLUE = 1,
		GREEN = 2,
		CYAN = 3,
		RED = 4,
		MAGENTA = 5,
		YELLOW = 6,

		WHITE = 7,
		GRAY = 8,
		LIGHT_BLUE = 9,
		LIGHT_GREEN = 10,
		LIGHT_CYAN = 11,
		LIGHT_RED = 12,
		LIGHT_MAGENTA = 13,
		LIGHT_YELLOW = 14,
		BRIGHT_WHITE = 15;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (color)
	{
	case TextColor::reset:
		SetConsoleTextAttribute(hConsole, WHITE | (BLACK << 4));
		break;
	case TextColor::black:
		SetConsoleTextAttribute(hConsole, BLACK | (BLACK << 4));
		break;
	case TextColor::red:
		SetConsoleTextAttribute(hConsole, RED | (BLACK << 4));
		break;
	case TextColor::green:
		SetConsoleTextAttribute(hConsole, GREEN | (BLACK << 4));
		break;
	case TextColor::yellow:
		SetConsoleTextAttribute(hConsole, YELLOW | (BLACK << 4));
		break;
	case TextColor::blue:
		SetConsoleTextAttribute(hConsole, BLUE | (BLACK << 4));
		break;
	case TextColor::magenta:
		SetConsoleTextAttribute(hConsole, MAGENTA | (BLACK << 4));
		break;
	case TextColor::cyan:
		SetConsoleTextAttribute(hConsole, CYAN | (BLACK << 4));
		break;
	case TextColor::white:
		SetConsoleTextAttribute(hConsole, WHITE | (BLACK << 4));
		break;
	default:
		break;
	}
}

NGS_HPP_INLINE void Console::SetBackgroundColor(TextColor color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	static constexpr byte
		BLACK = 0,
		BLUE = 1,
		GREEN = 2,
		CYAN = 3,
		RED = 4,
		MAGENTA = 5,
		YELLOW = 6,

		WHITE = 7,
		GRAY = 8,
		LIGHT_BLUE = 9,
		LIGHT_GREEN = 10,
		LIGHT_CYAN = 11,
		LIGHT_RED = 12,
		LIGHT_MAGENTA = 13,
		LIGHT_YELLOW = 14,
		BRIGHT_WHITE = 15;

	switch (color)
	{
	case TextColor::black:
		SetConsoleTextAttribute(hConsole, BLACK | (BLACK << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::red:
		SetConsoleTextAttribute(hConsole, BLACK | (RED << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::green:
		SetConsoleTextAttribute(hConsole, BLACK | (GREEN << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::yellow:
		SetConsoleTextAttribute(hConsole, BLACK | (YELLOW << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::blue:
		SetConsoleTextAttribute(hConsole, BLACK | (BLUE << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::magenta:
		SetConsoleTextAttribute(hConsole, BLACK | (MAGENTA << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::cyan:
		SetConsoleTextAttribute(hConsole, BLACK | (CYAN << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::white:
		SetConsoleTextAttribute(hConsole, BLACK | (WHITE << 4) | FOREGROUND_INTENSITY);
		break;
	default:
		break;
	}
}

#else

NGS_HPP_INLINE void Console::SetTextColor(TextColor color) {

}

NGS_HPP_INLINE void Console::SetBackgroundColor(TextColor color) {

}

#endif

#else

NGS_HPP_INLINE void Console::SetTextColor(TextColor color) {
	auto& os = std::cout;
	switch (color)
	{
	case TextColor::reset:
		os << "\033[0m";
		break;
	case TextColor::black:
		os << "\033[30m";
		break;
	case TextColor::red:
		os << "\033[31m";
		break;
	case TextColor::green:
		os << "\033[32m";
		break;
	case TextColor::yellow:
		os << "\033[33m";
		break;
	case TextColor::blue:
		os << "\033[34m";
		break;
	case TextColor::magenta:
		os << "\033[35m";
		break;
	case TextColor::cyan:
		os << "\033[36m";
		break;
	case TextColor::white:
		os << "\033[37m";
		break;
	default:
		break;
	}
}

NGS_HPP_INLINE void Console::SetBackgroundColor(TextColor color) {
	auto& os = std::cout;
	switch (color)
	{
	case TextColor::black:
		os << "\033[1m\033[30m";
		break;
	case TextColor::red:
		os << "\033[1m\033[31m";
		break;
	case TextColor::green:
		os << "\033[1m\033[32m";
		break;
	case TextColor::yellow:
		os << "\033[1m\033[33m";
		break;
	case TextColor::blue:
		os << "\033[1m\033[34m";
		break;
	case TextColor::magenta:
		os << "\033[1m\033[35m";
		break;
	case TextColor::cyan:
		os << "\033[1m\033[36m";
		break;
	case TextColor::white:
		os << "\033[1m\033[37m";
		break;
	default:
		break;
	}
}

#endif

NGS_END
