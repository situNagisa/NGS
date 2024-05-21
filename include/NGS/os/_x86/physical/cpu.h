#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct cpu
{
	NGS_PP_INJECT_BEGIN(cpu);
public:

	static void disable_interrupt()
	{
#if defined(NGS_COMPILER_IS_MSVC)
		__asm
		{
			cli
		}
#elif defined(NGS_COMPILER_IS_GCC)
		asm volatile("cli");
#elif defined(NGS_COMPILER_IS_CLANG)
		asm volatile("cli");
#endif
	}

	static void enable_interrupt()
	{
#if defined(NGS_COMPILER_IS_MSVC)
		__asm
		{
			sti
		}
#elif defined(NGS_COMPILER_IS_GCC)
		asm volatile("sti");
#elif defined(NGS_COMPILER_IS_CLANG)
		asm volatile("sti");
#endif
	}
};

NGS_LIB_MODULE_END