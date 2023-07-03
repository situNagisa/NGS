#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/STL.h"

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

template<typename T, typename Arg>
constexpr auto&& any_cast(const Arg& arg) {
	return const_cast<T>(*reinterpret_cast<const T*>(&arg));
}


NGS_END