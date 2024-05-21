#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct interrupt_descriptor_table
{
	NGS_PP_INJECT_BEGIN(interrupt_descriptor_table);
public:
	using underlying_type = ::std::uint64_t;

	::std::uint16_t size;
	::std::uint16_t address_low;
	::std::uint16_t address_high;

	void load_to_register() const
	{
		volatile pointer_t idt_ptr = reinterpret_cast<pointer_t>(this);
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
};

NGS_LIB_MODULE_END
