#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//x86 assemble
inline void input(::std::uint16_t port, ::std::uint8_t& result)
{
#if defined(NGS_COMPILER_IS_MSVC)
	__asm
	{
		mov dx, port
		in al, dx
		mov result, al
	}
#elif defined(NGS_COMPILER_IS_GCC)
	asm volatile("in %1,%0" : "=a" (result) : "d" (port));
#elif defined(NGS_COMPILER_IS_CLANG)
	asm volatile("inb %1,%0" : "=a" (result) : "d" (port));
#endif
}

inline void input(::std::uint16_t port, void* buffer, ::std::size_t size)
{
#if defined(NGS_COMPILER_IS_MSVC)
	__asm
	{
		mov dx, port
		mov edi, address
		mov ecx, count
		rep insb
	}
#elif defined(NGS_COMPILER_IS_GCC)
	asm volatile("cld; rep insl" : "=D" (address), "=c" (count) : "d" (port), "0" (address), "1" (count) : "memory", "cc");
#elif defined(NGS_COMPILER_IS_CLANG)
	asm volatile("cld; rep insl" : "=D" (address), "=c" (count) : "d" (port), "0" (address), "1" (count) : "memory", "cc");
#endif
}


NGS_LIB_MODULE_END