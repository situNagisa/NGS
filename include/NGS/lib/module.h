//#pragma once


#if !defined(NGS_LIB_BEGIN) || !defined(NGS_LIB_END)
#	error "NGS_LIB_BEGIN or NGS_LIB_END is not defined."
#else
#	if defined(NGS_LIB_MODULE_INLINE_NAME)
#		define NGS_LIB_MODULE_NAME NGS_LIB_MODULE_INLINE_NAME
#		define NGS_LIB_MODULE_BEGIN NGS_LIB_BEGIN inline namespace NGS_LIB_MODULE_NAME {
#		define NGS_LIB_MODULE_END } NGS_LIB_END
#	elif defined(NGS_LIB_MODULE_NAME)
#		define NGS_LIB_MODULE_BEGIN NGS_LIB_BEGIN namespace NGS_LIB_MODULE_NAME {
#		define NGS_LIB_MODULE_END } NGS_LIB_END
#	else
#		error "NGS_LIB_MODULE_NAME or NGS_LIB_MODULE_INLINE_NAME is not defined."
#	endif
#endif

#define NGS_LIB_MODULE_EXPORT(symbol)	\
NGS_LIB_BEGIN							\
using NGS_LIB_MODULE_NAME::symbol;		\
NGS_LIB_END								\
//
#define NGS_LIB_MODULE_EXPORT_NAMESPACE_ID(ns,id)	\
NGS_LIB_BEGIN										\
namespace id = NGS_LIB_MODULE_NAME::ns;				\
NGS_LIB_END											\
//

#define NGS_LIB_MODULE_EXPORT_NAMESPACE(ns) NGS_LIB_MODULE_EXPORT_NAMESPACE_ID(ns,ns)