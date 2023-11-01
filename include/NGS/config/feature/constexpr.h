#pragma once

#include "../defined.h"

#ifdef NGS_CPP_STANDARD_HAS_23
#	define NGS_CONSTEXPR23 constexpr
#else
#	define NGS_CONSTEXPR23 
#endif

#ifdef NGS_CPP_STANDARD_HAS_20
#	define NGS_CONSTEXPR20 constexpr
#else
#	define NGS_CONSTEXPR20 
#endif

#ifdef NGS_CPP_STANDARD_HAS_17
#	define NGS_CONSTEXPR17 constexpr
#else
#	define NGS_CONSTEXPR17 
#endif

#ifdef NGS_CPP_STANDARD_HAS_14
#	define NGS_CONSTEXPR14 constexpr
#else
#	define NGS_CONSTEXPR14 
#endif

#ifdef NGS_CPP_STANDARD_HAS_11
#	define NGS_CONSTEXPR11 constexpr
#else
#	define NGS_CONSTEXPR11 
#endif
