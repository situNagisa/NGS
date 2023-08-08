#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/basic.h"

NGS_BEGIN

#if NGS_COMPILER == NGS_MSVC
#define vprint vsprintf_s
#else
#define vprint vsprintf
#endif

inline nstring Format(nchar_ptr_cst fmt, ...) {
	nchar buffer[1024];
	va_list args;
	va_start(args, fmt);
	vprint(buffer, fmt, args);
	va_end(args);
	return buffer;
}

#undef vprint

NGS_END