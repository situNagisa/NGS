#pragma once

#define NGS_COMPILER_UNKNOWN	(0)
#define NGS_COMPILER_MSVC		(1)
#define NGS_COMPILER_CLANG		(2)
#define NGS_COMPILER_GCC		(3)
#define NGS_COMPILER_INTEL		(4)

#ifdef _MSC_VER

#	define NGS_COMPILER_IS_MSVC		true
#	define NGS_COMPILER NGS_COMPILER_MSVC

#elif defined(__clang__) or defined(__clang_major__)

#	define NGS_COMPILER_IS_CLANG	true
#	define NGS_COMPILER NGS_COMPILER_CLANG

#elif defined(__GNUC__)

#	define NGS_COMPILER_IS_GCC		true
#	define NGS_COMPILER NGS_COMPILER_GCC

#elif defined(__INTEL_COMPILER)

#	define NGS_COMPILER_IS_INTEL	true
#	define NGS_COMPILER NGS_COMPILER_INTEL

#else

#	define NGS_COMPILER NGS_COMPILER_UNKNOWN
#	warning "unknown compiler"

#endif

#if defined(__EDG__)

//  编译器是否用EDG前端
#	define NGS_COMPILER_USE_EDG		true

#endif