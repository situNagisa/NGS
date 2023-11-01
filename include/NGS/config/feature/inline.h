#pragma once

#include "../defined.h"

#if NGS_COMPILER_IS_MSVC
#	define NGS_ALWAYS_INLINE __forceinline
#elif NGS_COMPILER_IS_GCC or NGS_COMPILER_IS_CLANG
#	define NGS_ALWAYS_INLINE __attribute__((always_inline)) inline
#else
#	define NGS_ALWAYS_INLINE inline
#endif
