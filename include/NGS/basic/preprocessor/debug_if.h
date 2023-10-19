#pragma once

#include "../config.h"

#if NGS_BUILD_TYPE == NGS_DEBUG
#define NGS_DEBUG_EXPR(expr) expr
#else
#define NGS_DEBUG_EXPR(expr)
#endif

#if NGS_BUILD_TYPE == NGS_DEBUG
#define NGS_DEBUG_IF(condition,expr) if(condition){expr;}
#else
#define NGS_DEBUG_IF(condition,expr) 
#endif