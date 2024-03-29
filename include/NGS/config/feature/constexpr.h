﻿#pragma once

#include "../defined.h"

#ifdef NGS_CPP_STANDARD_HAS_26
#	define NGS_CONSTEXPR26 constexpr
#else
#	define NGS_CONSTEXPR26
#endif

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

#if defined(NGS_CPP_STANDARD_HAS_20) && defined(NGS_USE_HPP)
#	define NGS_CONSTEXPR_VIRTUAL constexpr
#else
#	define NGS_CONSTEXPR_VIRTUAL 
#endif
