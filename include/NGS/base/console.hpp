#pragma once

#include "NGS/base/console.h"
#include "NGS/base/config.h"

#if NGS_PLATFORM == NGS_WINDOWS

#include <windows.h>

#endif

NGS_BEGIN

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

NGS_HPP_INILNE void Console::SetTextColor(Console::Color color) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (color)
	{
	case Console::Color::RESERT:
		SetConsoleTextAttribute(hConsole, WHITE | (BLACK << 4));
		break;
	case Console::Color::BLACK:
		SetConsoleTextAttribute(hConsole, BLACK | (BLACK << 4));
		break;
	case Console::Color::RED:
		SetConsoleTextAttribute(hConsole, RED | (BLACK << 4));
		break;
	case Console::Color::GREEN:
		SetConsoleTextAttribute(hConsole, GREEN | (BLACK << 4));
		break;
	case Console::Color::YELLOW:
		SetConsoleTextAttribute(hConsole, YELLOW | (BLACK << 4));
		break;
	case Console::Color::BLUE:
		SetConsoleTextAttribute(hConsole, BLUE | (BLACK << 4));
		break;
	case Console::Color::MAGENTA:
		SetConsoleTextAttribute(hConsole, MAGENTA | (BLACK << 4));
		break;
	case Console::Color::CYAN:
		SetConsoleTextAttribute(hConsole, CYAN | (BLACK << 4));
		break;
	case Console::Color::WHITE:
		SetConsoleTextAttribute(hConsole, WHITE | (BLACK << 4));
		break;
	default:
		break;
	}
}

NGS_HPP_INILNE void Console::SetBackgroundColor(Console::Color color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (color)
	{
	case Console::Color::BLACK:
		SetConsoleTextAttribute(hConsole, BLACK | (BLACK << 4) | FOREGROUND_INTENSITY);
		break;
	case Console::Color::RED:
		SetConsoleTextAttribute(hConsole, BLACK | (RED << 4) | FOREGROUND_INTENSITY);
		break;
	case Console::Color::GREEN:
		SetConsoleTextAttribute(hConsole, BLACK | (GREEN << 4) | FOREGROUND_INTENSITY);
		break;
	case Console::Color::YELLOW:
		SetConsoleTextAttribute(hConsole, BLACK | (YELLOW << 4) | FOREGROUND_INTENSITY);
		break;
	case Console::Color::BLUE:
		SetConsoleTextAttribute(hConsole, BLACK | (BLUE << 4) | FOREGROUND_INTENSITY);
		break;
	case Console::Color::MAGENTA:
		SetConsoleTextAttribute(hConsole, BLACK | (MAGENTA << 4) | FOREGROUND_INTENSITY);
		break;
	case Console::Color::CYAN:
		SetConsoleTextAttribute(hConsole, BLACK | (CYAN << 4) | FOREGROUND_INTENSITY);
		break;
	case Console::Color::WHITE:
		SetConsoleTextAttribute(hConsole, BLACK | (WHITE << 4) | FOREGROUND_INTENSITY);
		break;
	default:
		break;
	}
}

#else

NGS_HPP_INILNE void Console::SetTextColor(Console::Color color) {
	auto& os = std::cout;
	switch (color)
	{
	case Console::Color::RESERT:
		os << "\033[0m";
		break;
	case Console::Color::BLACK:
		os << "\033[30m";
		break;
	case Console::Color::RED:
		os << "\033[31m";
		break;
	case Console::Color::GREEN:
		os << "\033[32m";
		break;
	case Console::Color::YELLOW:
		os << "\033[33m";
		break;
	case Console::Color::BLUE:
		os << "\033[34m";
		break;
	case Console::Color::MAGENTA:
		os << "\033[35m";
		break;
	case Console::Color::CYAN:
		os << "\033[36m";
		break;
	case Console::Color::WHITE:
		os << "\033[37m";
		break;
	default:
		break;
	}
}

NGS_HPP_INILNE void Console::SetBackgroundColor(Console::Color color) {
	auto& os = std::cout;
	switch (color)
	{
	case Console::Color::BLACK:
		os << "\033[1m\033[30m";
		break;
	case Console::Color::RED:
		os << "\033[1m\033[31m";
		break;
	case Console::Color::GREEN:
		os << "\033[1m\033[32m";
		break;
	case Console::Color::YELLOW:
		os << "\033[1m\033[33m";
		break;
	case Console::Color::BLUE:
		os << "\033[1m\033[34m";
		break;
	case Console::Color::MAGENTA:
		os << "\033[1m\033[35m";
		break;
	case Console::Color::CYAN:
		os << "\033[1m\033[36m";
		break;
	case Console::Color::WHITE:
		os << "\033[1m\033[37m";
		break;
	default:
		break;
	}
}

#endif

NGS_END
