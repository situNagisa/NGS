#pragma once

#include "../concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using vectors::ops::equal;

NGS_LIB_MODULE_END
NGS_MATH_MATRIX_OPERATOR_BEGIN

constexpr bool operator==(const operator_matrix auto& left, const operator_matrix auto& right)
	requires requires{ vectors::ops::equal(left, right); }
{
	return vectors::ops::equal(left, right);
}

NGS_MATH_MATRIX_OPERATOR_END