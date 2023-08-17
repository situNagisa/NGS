//==========================================================================================================
// @file	:	NGS/NGS_Version
// @CLR		:	4.0.30319.42000
// @author	:	NAGISA
// @data	:	2023/4/7 16:23:54
// @brief	:	
//==========================================================================================================
#pragma once

//_MSC_VER		MSVC
//__clang__		clang
//__GNUC__		gcc

#define NGS_WINDOWS	(1)
#define NGS_LINUX	(2)
#define NGS_MAC		(3)
#define NGS_ESP32	(4)

#ifdef __cplusplus
#define NGS_CPP (1)
#endif

#if defined(_WIN32) || defined(_WIN64)
#define NGS_PLATFORM NGS_WINDOWS
#elif defined(__linux__)
#define NGS_PLATFORM NGS_LINUX
#elif defined(__APPLE__)
#define NGS_PLATFORM NGS_MAC
#elif defined(ESP_PLATFORM)
#define NGS_PLATFORM NGS_ESP32
#else
#define NGS_PLATFORM 0
#error "NGS: unknown platform"
#endif



#define NGS_MSVC	(1)
#define NGS_CLANG	(2)
#define NGS_GCC		(3)
#define NGS_INTEL	(4)

#ifdef _MSC_VER

#define NGS_COMPILER NGS_MSVC

#elif defined(__clang__) || defined(__clang_major__)

#define NGS_COMPILER NGS_CLANG

#elif defined(__GNUC__)

#define NGS_COMPILER NGS_GCC

#elif defined(__INTEL_COMPILER)

#define NGS_COMPILER NGS_INTEL

#else

#define NGS_COMPILER 0
#error "NGS: Unknown compiler"

#endif

#if NGS_COMPILER == NGS_MSVC
#if defined(_MSVC_LANG) && _MSVC_LANG > __cplusplus
#define _NGS_CPP_STANDARD _MSVC_LANG
#else
#define _NGS_CPP_STANDARD __cplusplus
#endif
#else
#define _NGS_CPP_STANDARD __cplusplus
#endif

#if _NGS_CPP_STANDARD >= 199711L
#define NGS_HAS_CPP_03 1
#endif

#if _NGS_CPP_STANDARD >= 201103L
#define NGS_HAS_CPP_11 1
#endif

#if _NGS_CPP_STANDARD >= 201402L
#define NGS_HAS_CPP_14 1
#endif

#if _NGS_CPP_STANDARD > 201402L
#define NGS_HAS_CPP_17 1
#endif

#if _NGS_CPP_STANDARD > 201703L
#define NGS_HAS_CPP_20 1
#endif

#if _NGS_CPP_STANDARD > 202002L
#define NGS_HAS_CPP_23 1
#endif

#if NGS_HAS_CPP_23
#define NGS_CPP_23 1
#elif NGS_HAS_CPP_20
#define NGS_CPP_20 1
#elif NGS_HAS_CPP_17
#define NGS_CPP_17 1
#elif NGS_HAS_CPP_14
#define NGS_CPP_14 1
#elif NGS_HAS_CPP_11
#define NGS_CPP_11 1
#elif NGS_HAS_CPP_03
#define NGS_CPP_03 1
#endif

#if NGS_COMPILER == NGS_GCC
#define NGS_DEPRECATED(func) func __attribute__((deprecated))
#elif NGS_COMPILER == NGS_MSVC
#define NGS_DEPRECATED(func) __declspec(deprecated) func
#elif NGS_COMPILER == NGS_INTEL
#define NGS_DEPRECATED(func) __declspec(deprecated) func
#elif NGS_COMPILER == NGS_CLANG
#define NGS_DEPRECATED(func) [[deprecated]] func
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define DEPRECATED(func) func
#endif
