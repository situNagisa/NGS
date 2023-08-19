#pragma once

#include "NGS/base/defined.h"

NGS_BEGIN

#if NGS_COMPILER == NGS_MSVC
#define vprint vsprintf_s
#else
#define vprint vsprintf
#endif

inline nstring format(nchar_ptr_cst fmt, ...) {
	nchar buffer[1024];
	va_list args;
	va_start(args, fmt);
	vprint(buffer, fmt, args);
	va_end(args);
	return buffer;
}

#undef vprint

/**
 * \brief 一般情况下，我们不会使用这个函数，这个函数是用来在编译期获取一个类型的值。
 * 
 * \warning 此函数应与`decltype`关键字搭配使用，而不应该调用他，调用会导致未定义行为
 * 
 * \return 一个类型的值
 */
template<class _Type>
constexpr std::add_rvalue_reference_t<_Type> declval() {
	_Type* ptr = nullptr;
	return std::move(*ptr);
}

NGS_END