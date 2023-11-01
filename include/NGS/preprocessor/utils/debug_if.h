#pragma once

#include "../defined.h"

#if NGS_BUILD_TYPE_IS_DEBUG
#	define NGS_PP_DEBUG_EXPR(expr) (expr)
#else
#	define NGS_PP_DEBUG_EXPR(expr)
#endif

#if NGS_BUILD_TYPE_IS_DEBUG
#	define NGS_PP_DEBUG_IF(condition,expr) if(condition){expr;}
#else
#	define NGS_PP_DEBUG_IF(condition,expr) 
#endif