#pragma once

#include "../defined.h"
#include "./as_one_expression.h"

#if NGS_BUILD_TYPE_IS_DEBUG
#	define NGS_PP_DEBUG_EXPR(expr) NGS_PP_AS_ONE_EXPRESSION(expr)
#else
#	define NGS_PP_DEBUG_EXPR(expr)
#endif

#if NGS_BUILD_TYPE_IS_DEBUG
#	define NGS_PP_DEBUG_IF(condition,expr) NGS_PP_AS_ONE_EXPRESSION(if(condition){expr;})
#else
#	define NGS_PP_DEBUG_IF(condition,expr) 
#endif