#pragma once

#include "../register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

#if defined(NGS_COMPILER_IS_MSVC)
#	define NGS_OS_X86_ASM_READ_CONTROL(id,result) (nullptr)
#elif defined(NGS_COMPILER_IS_GCC) || defined(NGS_COMPILER_IS_CLANG)
#	define NGS_OS_X86_ASM_READ_CONTROL(id,result) asm volatile("movl %%" #id ", %0" : "=r" (result))
#endif

template<registers::register_tag T>
struct _read_functor
{
#if defined(__cpp_static_call_operator)
	static
#endif
	decltype(auto) operator()()
#if !defined(__cpp_static_call_operator)
	const
#endif
	{
		using tag_type = type_traits::naked_t<T>;
		constexpr auto bit_size = registers::register_bit_v<tag_type>();
		using result_type = bits::byte<bits::algorithm::bit_to_byte_ceil(bit_size)>;

		if constexpr(registers::control_register_tag<tag_type>)
		{
			volatile result_type result;
			if constexpr(cpt::naked_same_as<tag_type,registers::cr0>)
			{
				NGS_OS_X86_ASM_READ_CONTROL(cr0, result);
			}
			else if constexpr(cpt::naked_same_as<tag_type,registers::cr1>)
			{
				NGS_OS_X86_ASM_READ_CONTROL(cr1, result);
			}
			else if constexpr(cpt::naked_same_as<tag_type,registers::cr2>)
			{
				NGS_OS_X86_ASM_READ_CONTROL(cr2, result);
			}
			else if constexpr(cpt::naked_same_as<tag_type,registers::cr3>)
			{
				NGS_OS_X86_ASM_READ_CONTROL(cr3, result);
			}
			else if constexpr(cpt::naked_same_as<tag_type,registers::cr4>)
			{
				NGS_OS_X86_ASM_READ_CONTROL(cr4, result);
			}
			return result;
		}
		if constexpr (registers::state_register_tag<tag_type>)
		{
			volatile result_type result{};
#if defined(NGS_COMPILER_IS_GCC) || defined(NGS_COMPILER_IS_CLANG)
			if constexpr (cpt::naked_same_as<tag_type,registers::flags>)
			{
				asm volatile("pushfl; popl %0" : "=r" (result));
			}
			else if constexpr (cpt::naked_same_as<tag_type,registers::eflags>)
			{
				asm volatile("pushfl; popl %0" : "=r" (result));
			}
#endif
			return result;
		}
	}
};

template<registers::register_tag T>
inline constexpr _read_functor<T> read{};

#undef NGS_OS_X86_ASM_READ_CONTROL

NGS_LIB_MODULE_END