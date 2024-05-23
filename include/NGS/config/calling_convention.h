#pragma once

#include "./defined.h"

#if defined(NGS_COMPILER_IS_MSVC)
#	define NGS_CONFIG_CALLING_CONVENTION_STDCALL __stdcall
#	define NGS_CONFIG_CALLING_CONVENTION_FAST __fastcall
#	define NGS_CONFIG_CALLING_CONVENTION_THISCALL __thiscall
#	define NGS_CONFIG_CALLING_CONVENTION_CDECL __cdecl
#elif defined(NGS_COMPILER_IS_GCC) || defined(NGS_COMPILER_IS_CLANG)
#	define NGS_CONFIG_CALLING_CONVENTION_STDCALL __attribute__((__stdcall__))
#	define NGS_CONFIG_CALLING_CONVENTION_FAST __attribute__((__fastcall__))
#	define NGS_CONFIG_CALLING_CONVENTION_THISCALL __attribute__((__thiscall__))
#	define NGS_CONFIG_CALLING_CONVENTION_CDECL __attribute__((__cdecl__))
#endif