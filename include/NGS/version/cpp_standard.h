#pragma once

#include "./compiler.h"


#if NGS_COMPILER_IS_MSVC && defined(_MSVC_LANG) && _MSVC_LANG > __cplusplus
#	define NGS_CPP_VERSION _MSVC_LANG
#else
#	define NGS_CPP_VERSION __cplusplus
#endif

#if NGS_CPP_VERSION >= 202302L
#	define NGS_CPP_STANDARD_HAS_23 true
#endif
#if NGS_CPP_VERSION >= 202002L
#	define NGS_CPP_STANDARD_HAS_20 true
#endif
#if NGS_CPP_VERSION >= 201703L
#	define NGS_CPP_STANDARD_HAS_17 true
#endif
#if NGS_CPP_VERSION >= 201402L
#	define NGS_CPP_STANDARD_HAS_14 true
#endif
#if NGS_CPP_VERSION >= 201103L
#	define NGS_CPP_STANDARD_HAS_11 true
#endif
#if NGS_CPP_VERSION >= 199711L
#	define NGS_CPP_STANDARD_HAS_03 true
#endif

#ifdef NGS_CPP_STANDARD_HAS_23
#	define NGS_CPP_STANDARD_IS_23 true
#elif NGS_CPP_STANDARD_HAS_20
#	define NGS_CPP_STANDARD_IS_20 true
#elif NGS_CPP_STANDARD_HAS_17
#	define NGS_CPP_STANDARD_IS_17 true
#elif NGS_CPP_STANDARD_HAS_14
#	define NGS_CPP_STANDARD_IS_14 true
#elif NGS_CPP_STANDARD_HAS_11
#	define NGS_CPP_STANDARD_IS_11 true
#elif NGS_CPP_STANDARD_HAS_03
#	define NGS_CPP_STANDARD_IS_03 true
#endif