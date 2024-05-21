#pragma once

#include "../register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<registers::register_tag From, registers::register_tag To>
decltype(auto) move()
{

}

#if defined(NGS_COMPILER_IS_MSVC)
#	define NGS_OS_X86_ASM_MOVE_REGISTER(from,temp,to)	\
__asm													\
{														\
	mov temp, from										\
	mov to, temp										\
}														\
//
#elif defined(NGS_COMPILER_IS_GCC) || defined(NGS_COMPILER_IS_CLANG)
#	define NGS_OS_X86_ASM_MOVE_REGISTER(from,temp,to)	\
asm volatile("movl %0, %%" #to : : "r" (from))			\
//
#endif

template<registers::register_tag T>
decltype(auto) move(bits::bitsets::underlying_type_t<T> value)
{
	using tag_type = type_traits::naked_t<T>;
	if constexpr (registers::control_register_tag<tag_type>)
	{
		if constexpr(cpt::naked_same_as<tag_type, registers::cr3>)
		{
			NGS_OS_X86_ASM_MOVE_REGISTER(value, eax, cr3);
		}
		else if constexpr(cpt::naked_same_as<tag_type, registers::cr4>)
		{
			NGS_OS_X86_ASM_MOVE_REGISTER(value, eax, cr4);
		}
	}
}

NGS_LIB_MODULE_END