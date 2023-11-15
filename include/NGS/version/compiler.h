#pragma once

#define NGS_COMPILER_UNKNOWN	(0)
#define NGS_COMPILER_MSVC		(1)
#define NGS_COMPILER_CLANG		(2)
#define NGS_COMPILER_GCC		(3)
#define NGS_COMPILER_INTEL		(4)

#ifdef _MSC_VER

#	define NGS_COMPILER_IS_MSVC		true
#	define NGS_COMPILER NGS_COMPILER_MSVC
#	define NGS_COMPILER_VERSION		_MSC_VER
#	define NGS_COMPILER_VERSION_MAJOR	(_MSC_VER / 100)
#	define NGS_COMPILER_VERSION_MINOR	(_MSC_VER % 100)

#elif defined(__clang__) or defined(__clang_major__)

#	define NGS_COMPILER_IS_CLANG	true
#	define NGS_COMPILER NGS_COMPILER_CLANG
#	define NGS_COMPILER_VERSION		(__clang_major__ * 100 + __clang_minor__)
#	define NGS_COMPILER_VERSION_MAJOR	__clang_major__
#	define NGS_COMPILER_VERSION_MINOR	__clang_minor__

#elif defined(__GNUC__)

#	define NGS_COMPILER_IS_GCC		true
#	define NGS_COMPILER NGS_COMPILER_GCC
#	define NGS_COMPILER_VERSION		(__GNUC__ * 100 + __GNUC_MINOR__)
#	define NGS_COMPILER_VERSION_MAJOR	__GNUC__
#	define NGS_COMPILER_VERSION_MINOR	__GNUC_MINOR__

#elif defined(__INTEL_COMPILER)

#	define NGS_COMPILER_IS_INTEL	true
#	define NGS_COMPILER NGS_COMPILER_INTEL
#	define NGS_COMPILER_VERSION		__INTEL_COMPILER
#	define NGS_COMPILER_VERSION_MAJOR	(__INTEL_COMPILER / 100)
#	define NGS_COMPILER_VERSION_MINOR	(__INTEL_COMPILER % 100)

#else

#	define NGS_COMPILER NGS_COMPILER_UNKNOWN
#	warning "unknown compiler"

#endif

#define NGS_COMPILER_VERSION_IS_AT_LEAST(major, minor) (NGS_COMPILER_VERSION >= ((major) * 100 + (minor)))

#if defined(__EDG__)

//  编译器是否用EDG前端
#	define NGS_COMPILER_USE_EDG		true

#endif