//==========================================================================================================
// @file	:	NGS/NGS_Config
// @CLR		:	4.0.30319.42000
// @author	:	NAGISA
// @data	:	2023/4/7 16:23:33
// @brief	:	
//==========================================================================================================
#pragma once

#include "./version.h"

//===============
// build type
//===============
#define NGS_DEBUG 0
#define NGS_RELEASE 1

#ifndef NGS_BUILD_TYPE

#if defined(_DEBUG) || defined(Debug)
#define NGS_BUILD_TYPE NGS_DEBUG
#else
#define NGS_BUILD_TYPE NGS_RELEASE
#endif

#endif

//===============
// attribute
//===============

#if NGS_COMPILER == NGS_MSVC
#define NGS_NO_RETURN __declspec(noreturn)
#define NGS_ALWAYS_INLINE __forceinline
#define NGS_NO_INLINE __declspec(noinline)
#else
#define NGS_NO_RETURN __attribute__((noreturn))
#define NGS_ALWAYS_INLINE __attribute__((always_inline))
#define NGS_NO_INLINE __attribute__((noinline))
#endif

#define NGS_NO_DISCARD [[nodiscard]]

//===============
// hpp
//===============

#ifdef NGS_USE_HPP
#define NGS_HPP_INLINE inline
#define NGS_HPP_GLOBAL_STATIC inline
#else
#define NGS_HPP_INLINE 
#define NGS_HPP_GLOBAL_STATIC static
#endif

//===============
// dll
//===============

#if NGS_PLATFORM == NGS_WINDOWS
#define NGS_API_EXPORT __declspec(dllexport)
#define NGS_API_IMPORT __declspec(dllimport)
#else
#define NGS_API_EXPORT __attribute__((__visibility__("default")))
#define NGS_API_IMPORT __attribute__((__visibility__("default")))
#endif

#if		defined(NGS_DYNAMIC_LIBRARY_EXPORTS)
#define NGS_API NGS_API_EXPORT
#elif	defined(NGS_DYNAMIC_LIBRARY_IMPORTS)
#define NGS_API NGS_API_IMPORT
#else
#define NGS_API
#endif





