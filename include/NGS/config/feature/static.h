#pragma once

#include "../defined.h"

#ifdef NGS_CPP_STANDARD_HAS_26
#	define NGS_CONFIG_STATIC_26 static
#else
#	define NGS_CONFIG_STATIC_26
#endif

#ifdef NGS_CPP_STANDARD_HAS_23
#	define NGS_CONFIG_STATIC_23 static
#else
#	define NGS_CONFIG_STATIC_23
#endif

#ifdef NGS_CPP_STANDARD_HAS_20
#	define NGS_CONFIG_STATIC_20 static
#else
#	define NGS_CONFIG_STATIC_20
#endif

#ifdef NGS_CPP_STANDARD_HAS_17
#	define NGS_CONFIG_STATIC_17 static
#else
#	define NGS_CONFIG_STATIC_17
#endif

#ifdef NGS_CPP_STANDARD_HAS_14
#	define NGS_CONFIG_STATIC_14 static
#else
#	define NGS_CONFIG_STATIC_14
#endif

#ifdef NGS_CPP_STANDARD_HAS_11
#	define NGS_CONFIG_STATIC_11 static
#else
#	define NGS_CONFIG_STATIC_11
#endif

#ifdef NGS_CPP_STANDARD_HAS_03
#	define NGS_CONFIG_STATIC_03 static
#else
#	define NGS_CONFIG_STATIC_03
#endif