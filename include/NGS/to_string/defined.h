#pragma once

#include "NGS/basic/basic.h"


#define NGS_TO_STRING_NS to_strings

#define NGS_LIB_VERSION_MAJOR 0
#define NGS_LIB_VERSION_MINOR 1
#define NGS_LIB_VERSION_PATCH 0

#define NGS_LIB_NAME NGS_TO_STRING_NS
#include "NGS/lib/lib.h"

#if (defined(NGS_COMPILER_IS_GCC) and NGS_COMPILER_VERSION_IS_AT_LEAST(12, 0)) or !defined(NGS_COMPILER_IS_GCC)
#	define NGS_TOSTRING_STRING_CONSTEXPR constexpr
#else
#	define NGS_TOSTRING_STRING_CONSTEXPR
#endif
