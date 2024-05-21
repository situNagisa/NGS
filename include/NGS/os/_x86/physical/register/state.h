#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct flags_register
{
	NGS_PP_INJECT_BEGIN(flags_register);
public:
	using underlying_type = ::std::uint32_t;

	underlying_type carry : 1;
	underlying_type	   : 1;//1
	underlying_type parity : 1;
	underlying_type    : 1;//0

	underlying_type auxiliary_carry : 1;
	underlying_type    : 1;//0
	underlying_type zero : 1;
	underlying_type sign : 1;

	underlying_type trap : 1;
	underlying_type interruptible : 1;
	underlying_type direction : 1;
	underlying_type overflow : 1;

	underlying_type io_privilege : 2;
	underlying_type nested_task : 1;
	underlying_type    : 1;//0

	underlying_type resume : 1;
	underlying_type visual_8086_mode : 1;
	underlying_type alignment_check_access_control : 1;
	underlying_type visual_interrupt : 1;

	underlying_type visual_interrupt_pending : 1;
	underlying_type identification : 1;
	underlying_type    : 10;//0

	static auto read_register()
	{
		::std::uint32_t result;
#if defined(NGS_COMPILER_IS_MSVC)
		__asm
		{
			mov eax, cr0
			mov result, eax
		}
#elif defined(NGS_COMPILER_IS_GCC)
		asm volatile("pushfl; popl %0" : "=r" (result));
#elif defined(NGS_COMPILER_IS_CLANG)
		asm volatile("pushfl; popl %0" : "=r" (result));
#endif
		return *reinterpret_cast<const self_type*>(result);
	}
};

NGS_LIB_MODULE_END