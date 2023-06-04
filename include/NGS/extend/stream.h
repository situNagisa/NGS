#pragma once

#include "NGS/base/base.h"
#include "NGS/extend/console.h"

NGS_BEGIN

inline std::basic_ostream<nchar>& operator<<(std::basic_ostream<nchar>& os, Console::Color color) {
	Console::SetTextColor(color);
	return os;
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
_SetTextColor(Console::Color::RESERT);	\
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
		_SetTextColor(Console::Color::RESERT);
		_Self() << string;
		_SetTextColor(Console::Color::RESERT);
#endif
	}

	void Trace(nchar_ptr_cst format, ...) {
#if NGS_BUILD_TYPE == NGS_DEBUG
		PRINT(Console::Color::RESERT)
#endif
	}

	void Log(nstring_view tag, nstring_view string) {
#if NGS_BUILD_TYPE == NGS_DEBUG
		_SetTextColor(Console::Color::GREEN);
		_Self() << tag;
		_SetTextColor(Console::Color::WHITE);
		_Self() << " -- " << string;
		_SetTextColor(Console::Color::RESERT);
#endif
	}

	void Log(nstring_view tag, nchar_ptr_cst format, ...) {
#if NGS_BUILD_TYPE == NGS_DEBUG
		_SetTextColor(Console::Color::GREEN);
		_Self() << tag;
		_SetTextColor(Console::Color::WHITE);
		_Self() << " -- ";
		PRINT(Console::Color::WHITE)
#endif
	}

	void Message(nstring_view string) {
#if NGS_BUILD_TYPE == NGS_DEBUG
		_SetTextColor(Console::Color::BLUE);
		_Self() << string;
		_SetTextColor(Console::Color::RESERT);
#endif
	}

	void Message(nchar_ptr_cst format, ...) {
#if NGS_BUILD_TYPE == NGS_DEBUG
		PRINT(Console::Color::BLUE)
#endif
	}

	void Warning(nstring_view string) {
#if NGS_BUILD_TYPE == NGS_DEBUG
		_SetTextColor(Console::Color::YELLOW);
		_Self() << string;
		_SetTextColor(Console::Color::RESERT);
#endif
	}

	void Warning(nchar_ptr_cst format, ...) {
#if NGS_BUILD_TYPE == NGS_DEBUG
		PRINT(Console::Color::YELLOW)
#endif
	}

	void Error(nstring_view string) {
		_SetTextColor(Console::Color::RED);
		_Self() << string;
		_SetTextColor(Console::Color::RESERT);
	}

	void Error(nchar_ptr_cst format, ...) {
		PRINT(Console::Color::RED)
	}
private:
	void _SetTextColor(Console::Color color) {
		Console::SetTextColor(color);
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