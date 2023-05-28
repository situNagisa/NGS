#pragma once

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL.h"
#include "NGS/NGS_Concepts.h"

#if NGS_PLATFORM == NGS_WINDOWS

#include <Windows.h>

#undef RGB
#undef ERROR
#endif

NGS_BEGIN

//the following are UBUNTU/LINUX ONLY terminal color codes.

enum class TextColor {
	RESERT,
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,

	BLACK_B,
	RED_B,
	GREEN_B,
	YELLOW_B,
	BLUE_B,
	MAGENTA_B,
	CYAN_B,
	WHITE_B,
};

template<typename CharT>
std::basic_ostream<CharT, std::char_traits<CharT>>& operator<<(std::basic_ostream<CharT, std::char_traits<CharT>>& os, TextColor color) {
#if NGS_PLATFORM == NGS_WINDOWS
	HANDLE hConsole = nullptr;
	if constexpr (std::is_same_v<CharT, char>) {
		if (os.rdbuf() == std::cout.rdbuf()) {
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		}
		else if (os.rdbuf() == std::cerr.rdbuf()) {
			hConsole = GetStdHandle(STD_ERROR_HANDLE);
		}
		else if (os.rdbuf() == std::clog.rdbuf()) {
			hConsole = GetStdHandle(STD_ERROR_HANDLE);
		}
	}
	else if constexpr (std::is_same_v<CharT, wchar_t>) {
		if (os.rdbuf() == std::wcout.rdbuf()) {
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		}
		else if (os.rdbuf() == std::wcerr.rdbuf()) {
			hConsole = GetStdHandle(STD_ERROR_HANDLE);
		}
		else if (os.rdbuf() == std::wclog.rdbuf()) {
			hConsole = GetStdHandle(STD_ERROR_HANDLE);
		}
	}
	else return os;

	if (!hConsole)return os;
	constexpr byte
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
	case TextColor::BLACK_B:
		SetConsoleTextAttribute(hConsole, BLACK | (BLACK << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::RED_B:
		SetConsoleTextAttribute(hConsole, BLACK | (RED << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::GREEN_B:
		SetConsoleTextAttribute(hConsole, BLACK | (GREEN << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::YELLOW_B:
		SetConsoleTextAttribute(hConsole, BLACK | (YELLOW << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::BLUE_B:
		SetConsoleTextAttribute(hConsole, BLACK | (BLUE << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::MAGENTA_B:
		SetConsoleTextAttribute(hConsole, BLACK | (MAGENTA << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::CYAN_B:
		SetConsoleTextAttribute(hConsole, BLACK | (CYAN << 4) | FOREGROUND_INTENSITY);
		break;
	case TextColor::WHITE_B:
		SetConsoleTextAttribute(hConsole, BLACK | (WHITE << 4) | FOREGROUND_INTENSITY);
		break;
	default:
		break;
	}
	return os;
#elif NGS_PLATFORM == NGS_LINUX || NGS_PLATFORM == NGS_ESP32
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
	case TextColor::BLACK_B:
		os << "\033[1m\033[30m";
		break;
	case TextColor::RED_B:
		os << "\033[1m\033[31m";
		break;
	case TextColor::GREEN_B:
		os << "\033[1m\033[32m";
		break;
	case TextColor::YELLOW_B:
		os << "\033[1m\033[33m";
		break;
	case TextColor::BLUE_B:
		os << "\033[1m\033[34m";
		break;
	case TextColor::MAGENTA_B:
		os << "\033[1m\033[35m";
		break;
	case TextColor::CYAN_B:
		os << "\033[1m\033[36m";
		break;
	case TextColor::WHITE_B:
		os << "\033[1m\033[37m";
		break;
	default:
		break;
	}
	return os;
#else
	return os;
#endif
}
template<typename T>
class basic_ostream : public std::basic_ostream<T, std::char_traits<T>> {
#if NGS_COMPILER == NGS_MSVC
#define vprint vsprintf_s
#else
#define vprint vsprintf
#endif
#define PRINT(color)				\
_SetTextColor(color);				\
nchar buffer[1024];					\
va_list args;						\
va_start(args, format);				\
vprint(buffer, format, args);		\
va_end(args);						\
_Self() << buffer;					\
_SetTextColor(TextColor::RESERT);	\
//
public:
	NGS_TYPE_DEFINE(basic_ostream<T>, this);
	using __base = std::basic_ostream<T, std::char_traits<T>>;

	static __base& GetDefaultOS() {
		if constexpr (std::is_same_v<T, char>) {
			return std::cout;
		}
		else if constexpr (std::is_same_v<T, wchar_t>) {
			return std::wcout;
		}
		else {
			//static_assert(false, "Not support type");
		}
	}
public:
	using __base::basic_ostream;

	void Trace(nstring_view string) {
#if NGS_BUILD_TYPE == NGS_DEBUG
		_SetTextColor(TextColor::RESERT);
		_Self() << string;
		_SetTextColor(TextColor::RESERT);
#endif
	}

	void Trace(nchar_ptr_cst format, ...) {
#if NGS_BUILD_TYPE == NGS_DEBUG
		PRINT(TextColor::RESERT)
#endif
	}

	void Log(nstring_view tag, nstring_view string) {
#if NGS_BUILD_TYPE == NGS_DEBUG
		_SetTextColor(TextColor::GREEN);
		_Self() << tag;
		_SetTextColor(TextColor::WHITE);
		_Self() << " -- " << string;
		_SetTextColor(TextColor::RESERT);
#endif
	}

	void Log(nstring_view tag, nchar_ptr_cst format, ...) {
#if NGS_BUILD_TYPE == NGS_DEBUG
		_SetTextColor(TextColor::GREEN);
		_Self() << tag;
		_SetTextColor(TextColor::WHITE);
		_Self() << " -- ";
		PRINT(TextColor::WHITE)
#endif
	}

	void Message(nstring_view string) {
#if NGS_BUILD_TYPE == NGS_DEBUG
		_SetTextColor(TextColor::BLUE);
		_Self() << string;
		_SetTextColor(TextColor::RESERT);
#endif
	}

	void Message(nchar_ptr_cst format, ...) {
#if NGS_BUILD_TYPE == NGS_DEBUG
		PRINT(TextColor::BLUE)
#endif
	}

	void Warning(nstring_view string) {
#if NGS_BUILD_TYPE == NGS_DEBUG
		_SetTextColor(TextColor::YELLOW);
		_Self() << string;
		_SetTextColor(TextColor::RESERT);
#endif
	}

	void Warning(nchar_ptr_cst format, ...) {
#if NGS_BUILD_TYPE == NGS_DEBUG
		PRINT(TextColor::YELLOW)
#endif
	}

	void Error(nstring_view string) {
		_SetTextColor(TextColor::RED);
		_Self() << string;
		_SetTextColor(TextColor::RESERT);
	}

	void Error(nchar_ptr_cst format, ...) {
		PRINT(TextColor::RED)
	}
private:
	void _SetTextColor(TextColor color) {
		*this << color;
	}
	__this_ref _Self() { return *this; }
	__this_ref_cst _Self()const { return *this; }
private:


#undef vprint
#undef PRINT(color)
};

using nostream = basic_ostream<nchar>;

inline nostream nos(nostream::GetDefaultOS().rdbuf());


NGS_END