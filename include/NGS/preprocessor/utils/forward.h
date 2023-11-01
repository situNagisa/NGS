#pragma once

#include "./type_of_expression.h"

#define NGS_PP_PERFECT_FORWARD(x) ::std::forward<NGS_PP_EXPRESSION_TYPE(x)>(x)