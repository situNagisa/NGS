#pragma once

#include "./defined.h"

NGS_TOSTRING_BEGIN

#if NGS_COMPILER_IS_MSVC
#define vprint vsprintf_s
#else
#define vprint vsprintf
#endif

inline std::string format(std::string_view fmt, ...) {
	char buffer[1024];
	va_list args;
	va_start(args, fmt);
	vprint(buffer, fmt.data(), args);
	va_end(args);
	return buffer;
}

#undef vprint

NGS_TOSTRING_END