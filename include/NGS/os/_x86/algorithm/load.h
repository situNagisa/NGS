#pragma once

#include "../pointer.h"
#include "../physical.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

inline void load_gdt(const physical::registers::global_descriptor_table& gdt)
{
	volatile pointer_t gdt_ptr = reinterpret_cast<pointer_t>(&gdt);
#if defined(NGS_COMPILER_IS_MSVC)
	__asm
	{
		lgdt fword ptr[gdt_ptr]
	}
#elif defined(NGS_COMPILER_IS_GCC)
	asm volatile("lgdt %0" : : "r" (gdt_ptr));
#elif defined(NGS_COMPILER_IS_CLANG)
	asm volatile("lgdt %0" : : "r" (gdt_ptr));
#endif
}

inline void load_idt(const physical::registers::interrupt_descriptor_table& idt)
{
	volatile pointer_t idt_ptr = reinterpret_cast<pointer_t>(&idt);
#if defined(NGS_COMPILER_IS_MSVC)
	__asm
	{
		lidt fword ptr[idt_ptr]
	}
#elif defined(NGS_COMPILER_IS_GCC)
	asm volatile("lidt %0" : : "r" (idt_ptr));
#elif defined(NGS_COMPILER_IS_CLANG)
	asm volatile("lidt %0" : : "r" (idt_ptr));
#endif
}

NGS_LIB_MODULE_END