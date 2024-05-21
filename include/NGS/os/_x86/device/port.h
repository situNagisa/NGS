#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct port
{
	using value_type = ::std::uint16_t;

	constexpr port(value_type value)
		: _value(value)
	{}

	::std::uint8_t input() const
	{
		::std::uint8_t result;
		input(result);
		return result;
	}

	void input(::std::uint8_t& result) const
	{
#if defined(NGS_COMPILER_IS_MSVC)
		/*__asm
		{
			mov dx, _value
			in al, dx
			mov result, al
		}*/
#elif defined(NGS_COMPILER_IS_GCC)
		asm volatile("in %1,%0" : "=a" (result) : "d" (_value));
#elif defined(NGS_COMPILER_IS_CLANG)
		asm volatile("inb %1,%0" : "=a" (result) : "d" (_value));
#endif
	}

	void input(void* address, ::std::size_t size) const
	{
#if defined(NGS_COMPILER_IS_MSVC)
		/*__asm
		{
			mov dx, _value
			mov edi, address
			mov ecx, size
			rep insb
		}*/
#elif defined(NGS_COMPILER_IS_GCC)
		asm volatile("cld; rep insl" : "=D" (address), "=c" (size) : "d" (_value), "0" (address), "1" (size) : "memory", "cc");
#elif defined(NGS_COMPILER_IS_CLANG)
		asm volatile("cld; rep insl" : "=D" (address), "=c" (size) : "d" (_value), "0" (address), "1" (size) : "memory", "cc");
#endif
	}

	void output(::std::uint8_t data) const
	{
#if defined(NGS_COMPILER_IS_MSVC)
		/*__asm
		{
			mov dx, _value
			mov al, data
			out dx, al
		}*/
#elif defined(NGS_COMPILER_IS_GCC)
		asm volatile("out %0,%1" : : "a" (data), "d" (_value));
#elif defined(NGS_COMPILER_IS_CLANG)
		asm volatile("outb %0,%1" : : "a" (data), "d" (_value));
#endif
	}

	void output(::std::uint16_t data) const
	{
#if defined(NGS_COMPILER_IS_MSVC)
		/*__asm
		{
			mov dx, _value
			mov ax, data
			out dx, ax
		}*/
#elif defined(NGS_COMPILER_IS_GCC)
		asm volatile("out %0,%1" : : "a" (data), "d" (_value));
#elif defined(NGS_COMPILER_IS_CLANG)
		asm volatile("outw %0,%1" : : "a" (data), "d" (_value));
#endif
	}

	void output(void* address, ::std::size_t size) const
	{
#if defined(NGS_COMPILER_IS_MSVC)
		/*__asm
		{
			mov dx, _value
			mov esi, address
			mov ecx, size
			rep outsb
		}*/
#elif defined(NGS_COMPILER_IS_GCC)
		asm volatile("cld; rep outsl" : "=S" (address), "=c" (size) : "d" (_value), "0" (address), "1" (size) : "cc");
#elif defined(NGS_COMPILER_IS_CLANG)
		asm volatile("cld; rep outsl" : "=S" (address), "=c" (size) : "d" (_value), "0" (address), "1" (size) : "cc");
#endif
	}

	value_type _value;
};

NGS_LIB_MODULE_END