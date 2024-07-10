#pragma once

#include "../register.h"
#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct control0_register
{
	NGS_PP_INJECT_BEGIN(control0_register);
public:
	using underlying_type = register_underlying_t;
	using register_category_type = tags::cr0;

	underlying_type protected_enable : 1;
	underlying_type monitor_coprocessor : 1;
	underlying_type emulation : 1;
	underlying_type task_switched : 1;

	underlying_type extension_type : 1;
	underlying_type numeric_error : 1;
	underlying_type : 2;

	underlying_type : 4;

	underlying_type : 4;

	underlying_type write_protect : 1;
	underlying_type : 1;
	underlying_type alignment_mask : 1;
	underlying_type : 1;

	underlying_type : 4;

	underlying_type : 4;

	underlying_type : 1;
	underlying_type not_write_through : 1;
	underlying_type cache_disable : 1;
	underlying_type paging : 1;
};

struct control1_register : trivial_register< tags::cr0>{};

struct control2_register
{
	NGS_PP_INJECT_BEGIN(control2_register);
public:
	using underlying_type = register_underlying_t;
	using register_category_type = tags::cr2;

	underlying_type address;
};

struct control3_register
{
	NGS_PP_INJECT_BEGIN(control3_register);
public:
	using underlying_type = register_underlying_t;
	using register_category_type = tags::cr3;

	underlying_type : 3;
	underlying_type page_level_write_through : 1;
	underlying_type page_level_cache_disable : 1;
	underlying_type : 7;
	underlying_type base : 20;
#if 0
	void load_to_register() const
	{
		volatile auto value = *reinterpret_cast<const ::std::uint32_t*>(this);
#if defined(NGS_COMPILER_IS_MSVC)
		__asm
		{
			mov eax, value
			mov cr3, eax
		}
#elif defined(NGS_COMPILER_IS_GCC)
		asm volatile("movl %0, %%cr3" : : "r" (value));
#elif defined(NGS_COMPILER_IS_CLANG)
		asm volatile("movl %0, %%cr3" : : "r" (value));
#endif
	}
#endif
};

struct control4_register
{
	NGS_PP_INJECT_BEGIN(control4_register);
public:
	using underlying_type = register_underlying_t;
	using register_category_type = tags::cr4;

	underlying_type vme : 1;
	underlying_type pvi : 1;
	underlying_type tsd : 1;
	underlying_type de : 1;
	underlying_type pse : 1;
	underlying_type pae : 1;
	underlying_type mce : 1;
	underlying_type pge : 1;
	underlying_type pce : 1;
	underlying_type osfxsr : 1;
	underlying_type osxmmexcpt : 1;
	underlying_type : 2;
	underlying_type vmxe : 1;
	underlying_type smxe : 1;
	underlying_type : 2;
	underlying_type pcide : 1;
	underlying_type osxsave : 1;
	underlying_type : 1;
	underlying_type smep : 1;
};

NGS_LIB_MODULE_END
