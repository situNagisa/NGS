#pragma once

#include "./defined.h"

#define NGS_BUILD_DEBUG		(0)
#define NGS_BUILD_RELEASE	(1)

#if NGS_COMPILER_IS_MSVC
#	ifdef _DEBUG
#		define NGS_BUILD_TYPE NGS_BUILD_DEBUG
#	else
#		define NGS_BUILD_TYPE NGS_BUILD_RELEASE
#	endif
#elif NGS_COMPILER_IS_GCC or NGS_COMPILER_IS_CLANG
#	ifdef NDEBUG
#		define NGS_BUILD_TYPE NGS_BUILD_RELEASE
#	elif defined(__DEBUG) or defined(_DEBUG)
#		define NGS_BUILD_TYPE NGS_BUILD_DEBUG
#	else
#		define NGS_BUILD_TYPE NGS_BUILD_RELEASE
#	endif
#else
#	define NGS_BUILD_TYPE 
#endif

#if NGS_BUILD_TYPE == NGS_BUILD_DEBUG
#	define NGS_BUILD_TYPE_IS_DEBUG true
#endif

#if NGS_BUILD_TYPE == NGS_BUILD_RELEASE
#	define NGS_BUILD_TYPE_IS_RELEASE true
#endif
