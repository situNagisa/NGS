#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

#if defined(NGS_COMPILER_IS_MSVC)
#	define NGS_OS_X86_ASM_GENERAL_CODE(code) __asm { code }
#elif defined(NGS_COMPILER_IS_GCC)
#	define NGS_OS_X86_ASM_GENERAL_CODE(code) asm volatile(#code)
#elif defined(NGS_COMPILER_IS_CLANG)
#	define NGS_OS_X86_ASM_GENERAL_CODE(code) asm volatile(#code)
#endif

inline void disable_interrupt()
{
	NGS_OS_X86_ASM_GENERAL_CODE(cli);
}

inline void enable_interrupt()
{
	NGS_OS_X86_ASM_GENERAL_CODE(sti);
}

inline void lock()
{
	NGS_OS_X86_ASM_GENERAL_CODE(lock);
}

inline void condition_code()
{
	NGS_OS_X86_ASM_GENERAL_CODE(cc);
}


inline ::std::uint8_t input_byte(::std::uint16_t port)
{
	::std::uint8_t result;
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
	return result;
}

inline void output_byte(::std::uint16_t port, ::ngs::byte data)
{
#if defined(NGS_COMPILER_IS_MSVC)
	__asm
	{
		mov dx, port
		mov al, data
		out dx, al
	}
#elif defined(NGS_COMPILER_IS_GCC)
	asm volatile("out %0,%1" : : "a" (data), "d" (port));
#elif defined(NGS_COMPILER_IS_CLANG)
	asm volatile("outb %0,%1" : : "a" (data), "d" (port));
#endif
}

inline void output_word(::std::uint16_t port, ::std::uint16_t data)
{
#if defined(NGS_COMPILER_IS_MSVC)
	__asm
	{
		mov dx, port
		mov ax, data
		out dx, ax
	}
#elif defined(NGS_COMPILER_IS_GCC)
	asm volatile("out %0,%1" : : "a" (data), "d" (port));
#elif defined(NGS_COMPILER_IS_CLANG)
	asm volatile("outw %0,%1" : : "a" (data), "d" (port));
#endif
}

NGS_LIB_MODULE_END