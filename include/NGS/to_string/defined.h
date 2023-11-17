#pragma once

#include "NGS/basic/basic.h"
#include "NGS/cpt/cpt.h"

#define NGS_TOSTRING_BEGIN NGS_BEGIN inline namespace to_strings{
#define NGS_TOSTRING_END }NGS_END

#if (defined(NGS_COMPILER_IS_GCC) and NGS_COMPILER_VERSION_IS_AT_LEAST(12, 0)) or !defined(NGS_COMPILER_IS_GCC)
#	define NGS_TOSTRING_STRING_CONSTEXPR constexpr
#else
#	define NGS_TOSTRING_STRING_CONSTEXPR
#endif
