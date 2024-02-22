//#pragma once

#include "./defined.h"

#if defined(NGS_LIB_BEGIN) || defined(NGS_LIB_END)
#	error "NGS_LIB_BEGIN or NGS_LIB_END is already defined."
#else

#	if defined(NGS_LIB_NAME)
#		define NGS_LIB_BEGIN NGS_BEGIN namespace NGS_LIB_NAME {
#		define NGS_LIB_END } NGS_END
#		define NGS_LIB_FULL_QUALIFIER_NAME NGS_ NGS_LIB_NAME
#	elif defined(NGS_LIB_INLINE_NAME)
#		define NGS_LIB_NAME NGS_LIB_INLINE_NAME
#		define NGS_LIB_BEGIN NGS_BEGIN inline namespace NGS_LIB_NAME {
#		define NGS_LIB_END } NGS_END
#		define NGS_LIB_FULL_QUALIFIER_NAME NGS_ NGS_LIB_NAME
#	else
#		error "NGS_LIB_NAME or NGS_LIB_INLINE_NAME is not defined."
#	endif

#endif

#if defined(NGS_LIB_VERSION)
#elif defined(NGS_LIB_VERSION_MAJOR) && defined(NGS_LIB_VERSION_MINOR) &&  defined(NGS_LIB_VERSION_PATCH)
#	define NGS_LIB_VERSION NGS_PP_VERSION(NGS_LIB_VERSION_MAJOR, NGS_LIB_VERSION_MINOR, NGS_LIB_VERSION_PATCH)
#else
#	error "NGS_LIB_VERSION is not defined."
#endif

#if defined(NGS_LIB_VERSION)
NGS_LIB_BEGIN

struct lib_version
{
	constexpr static size_t major = NGS_PP_VERSION_MAJOR(NGS_LIB_VERSION);
	constexpr static size_t minor = NGS_PP_VERSION_MINOR(NGS_LIB_VERSION);
	constexpr static size_t patch = NGS_PP_VERSION_PATCH(NGS_LIB_VERSION);

	constexpr static size_t version = NGS_PP_VERSION(major, minor, patch);
};

NGS_LIB_END
#endif