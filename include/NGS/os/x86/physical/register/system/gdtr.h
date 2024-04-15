#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct global_descriptor_table
{
	NGS_MPL_ENVIRON_BEGIN(global_descriptor_table);
public:
	using underlying_type = ::std::uint64_t;
	
	::std::uint16_t size;
	::std::uint16_t address_low;
	::std::uint16_t address_high;

	void load_to_register() const
	{
		volatile pointer_t gdt_ptr = reinterpret_cast<pointer_t>(this);
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
};

NGS_LIB_MODULE_END