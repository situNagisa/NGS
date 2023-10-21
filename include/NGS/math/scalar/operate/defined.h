#pragma once

#include "../config.h"
#include "../defined.h"

#include "../expression.h"
#include "../container.h"

#if NGS_MATH_SCALAR_IMMEDIATE_EVALUATION

#	define NGS_MATH_SCALAR_IMMEDIATE_BEGIN NGS_MATH_SCALAR_BEGIN inline namespace immediate{
#	define NGS_MATH_SCALAR_IMMEDIATE_END } NGS_MATH_SCALAR_END
#	define NGS_MATH_SCALAR_EXPRESSION_BEGIN NGS_MATH_SCALAR_BEGIN namespace expression{
#	define NGS_MATH_SCALAR_EXPRESSION_END } NGS_MATH_SCALAR_END

#else

#	define NGS_MATH_SCALAR_IMMEDIATE_BEGIN NGS_MATH_SCALAR_BEGIN namespace immediate{
#	define NGS_MATH_SCALAR_IMMEDIATE_END } NGS_MATH_SCALAR_END
#	define NGS_MATH_SCALAR_EXPRESSION_BEGIN NGS_MATH_SCALAR_BEGIN inline namespace expression{
#	define NGS_MATH_SCALAR_EXPRESSION_END } NGS_MATH_SCALAR_END

#endif
