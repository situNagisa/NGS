#pragma once

#include "./defined.h"

#if defined(__cpp_static_call_operator)
#	define NGS_CONFIG_STATIC_CALL_OPERATOR  static
#	define NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
#else
#	define NGS_CONFIG_STATIC_CALL_OPERATOR
#	define NGS_CONFIG_STATIC_CALL_OPERATOR_CONST  const
#endif