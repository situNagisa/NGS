#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct control0
{
	NGS_MPL_ENVIRON_BEGIN(control0);
public:
	using underlying_type = ::std::uint32_t;

	underlying_type pe : 1;
	underlying_type mp : 1;
	underlying_type em : 1;
	underlying_type ts : 1;
	underlying_type et : 1;
	underlying_type ne : 1;
	underlying_type : 10;
	underlying_type wp : 1;
	underlying_type : 1;
	underlying_type am : 1;
	underlying_type : 10;
	underlying_type nw : 1;
	underlying_type cd : 1;
	underlying_type pg : 1;
};

using control1 = ::std::uint32_t;

struct control2
{
	NGS_MPL_ENVIRON_BEGIN(control2);
public:
	using underlying_type = ::std::uint32_t;

	underlying_type address;

	static auto read_register()
	{
		::std::uint32_t result;

#if defined(NGS_COMPILER_IS_MSVC)
		__asm
		{
			mov eax, cr2
			mov result, eax
		}
#elif defined(NGS_COMPILER_IS_GCC)
		asm volatile("movl %%cr2, %0" : "=r" (result));
#elif defined(NGS_COMPILER_IS_CLANG)
		asm volatile("movl %%cr2, %0" : "=r" (result));
#endif
		return self_type{ result };
	}
};

struct control3
{
	NGS_MPL_ENVIRON_BEGIN(control3);
public:
	using underlying_type = ::std::uint32_t;

	underlying_type : 3;
	underlying_type page_level_write_through : 1;
	underlying_type page_level_cache_disable : 1;
	underlying_type : 7;
	underlying_type base : 20;

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
};

struct control4
{
	NGS_MPL_ENVIRON_BEGIN(control4);
public:
	using underlying_type = ::std::uint32_t;

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
