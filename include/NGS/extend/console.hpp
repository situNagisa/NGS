#pragma once

#include "NGS/extend/console.h"

#if NGS_PLATFORM == NGS_WINDOWS

#include <windows.h>

#endif

NGS_BEGIN

static bool _s_set_text_color = [] {
	Debugger::set_text_color = Console::SetTextColor;
	return true;
}();

#if NGS_PLATFORM == NGS_WINDOWS

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

NGS_HPP_INLINE void Console::SetTextColor(TextColor color) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (color)
	{
	case TextColor::RESERT:
		SetConsoleTextAttribute(hConsole, WHITE | (BLACK << 4));
		break;
	case TextColor::BLACK:
		SetConsoleTextAttribute(hConsole, BLACK | (BLACK << 4));
		break;
	case TextColor::RED:
		SetConsoleTextAttribute(hConsole, RED | (BLACK << 4));
		break;
	case TextColor::GREEN:
		SetConsoleTextAttribute(hConsole, GREEN | (BLACK << 4));
		break;
	case TextColor::YELLOW:
		SetConsoleTextAttribute(hConsole, YELLOW | (BLACK << 4));
		break;
	case TextColor::BLUE:
		SetConsoleTextAttribute(hConsole, BLUE | (BLACK << 4));
		break;
	case TextColor::MAGENTA:
		SetConsoleTextAttribute(hConsole, MAGENTA | (BLACK << 4));
		break;
	case TextColor::CYAN:
		SetConsoleTextAttribute(hConsole, CYAN | (BLACK << 4));
		break;
	case TextColor::WHITE:
		SetConsoleTextAttribute(hConsole, WHITE | (BLACK << 4));
		break;
	default:
		break;
	}
}

NGS_HPP_INLINE void Console::SetBackgroundColor(TextColor color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (color)
	{
	case TextColor::BLACK:
		SetConsoleTextAttribute(hConsole, BLACK | (BLACK << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::RED:
		SetConsoleTextAttribute(hConsole, BLACK | (RED << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::GREEN:
		SetConsoleTextAttribute(hConsole, BLACK | (GREEN << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::YELLOW:
		SetConsoleTextAttribute(hConsole, BLACK | (YELLOW << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::BLUE:
		SetConsoleTextAttribute(hConsole, BLACK | (BLUE << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::MAGENTA:
		SetConsoleTextAttribute(hConsole, BLACK | (MAGENTA << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::CYAN:
		SetConsoleTextAttribute(hConsole, BLACK | (CYAN << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::WHITE:
		SetConsoleTextAttribute(hConsole, BLACK | (WHITE << 4) | FOREGROUND_INTENSITY);
		break;
	default:
		break;
	}
}

#else

NGS_HPP_INLINE void Console::SetTextColor(TextColor color) {
	auto& os = std::cout;
	switch (color)
	{
	case TextColor::RESERT:
		os << "\033[0m";
		break;
	case TextColor::BLACK:
		os << "\033[30m";
		break;
	case TextColor::RED:
		os << "\033[31m";
		break;
	case TextColor::GREEN:
		os << "\033[32m";
		break;
	case TextColor::YELLOW:
		os << "\033[33m";
		break;
	case TextColor::BLUE:
		os << "\033[34m";
		break;
	case TextColor::MAGENTA:
		os << "\033[35m";
		break;
	case TextColor::CYAN:
		os << "\033[36m";
		break;
	case TextColor::WHITE:
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
	case TextColor::BLACK:
		os << "\033[1m\033[30m";
		break;
	case TextColor::RED:
		os << "\033[1m\033[31m";
		break;
	case TextColor::GREEN:
		os << "\033[1m\033[32m";
		break;
	case TextColor::YELLOW:
		os << "\033[1m\033[33m";
		break;
	case TextColor::BLUE:
		os << "\033[1m\033[34m";
		break;
	case TextColor::MAGENTA:
		os << "\033[1m\033[35m";
		break;
	case TextColor::CYAN:
		os << "\033[1m\033[36m";
		break;
	case TextColor::WHITE:
		os << "\033[1m\033[37m";
		break;
	default:
		break;
	}
}

#endif

NGS_END
