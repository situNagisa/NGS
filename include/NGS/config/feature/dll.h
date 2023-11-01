#pragma once

#include "../defined.h"

#if NGS_SYSTEM_IS_WINDOWS

#	define NGS_DLL_EXPORT __declspec(dllexport)
#	define NGS_DLL_IMPORT __declspec(dllimport)

#else

#	define NGS_DLL_EXPORT __attribute__((visibility("default")))
#	define NGS_DLL_IMPORT __attribute__((visibility("default")))

#endif

#if		defined(NGS_DYNAMIC_LIBRARY_EXPORTS)
#	define NGS_DLL_API NGS_API_EXPORT
#elif	defined(NGS_DYNAMIC_LIBRARY_IMPORTS)
#	define NGS_DLL_API NGS_API_IMPORT
#else
#	define NGS_DLL_API
#endif
