#pragma once

#include "NGS/extend/console.h"

//inline std::basic_ostream<ngs::nchar>& operator<<(std::basic_ostream<ngs::nchar>& os, ngs::TextColor color) {
//	ngs::Console::SetTextColor(color);
//	return os;
//}

NGS_BEGIN

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