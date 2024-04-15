#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct extended_flags
{
	NGS_MPL_ENVIRON_BEGIN(extended_flags);
public:
	using underlying_type = ::std::uint32_t;

	underlying_type cs : 1;
	underlying_type	   : 1;
	underlying_type pf : 1;
	underlying_type    : 1;
	underlying_type af : 1;
	underlying_type    : 1;
	underlying_type zf : 1;
	underlying_type sf : 1;
	underlying_type tf : 1;
	underlying_type if_ : 1;
	underlying_type df : 1;
	underlying_type of : 1;
	underlying_type iopl : 2;
	underlying_type nt : 1;
	underlying_type    : 1;
	underlying_type rf : 1;
	underlying_type vm : 1;
	underlying_type ac : 1;
	underlying_type vif : 1;
	underlying_type vip : 1;
	underlying_type id : 1;
	underlying_type    : 10;

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