#pragma once

#include "NGS/math/matrix/concept.h"
#include "./access.h"

NGS_MATH_MATRIX_BEGIN

void swap_rows(functor::container auto&& matrix, size_t row1, size_t row2)
{
	auto r1 = row(matrix, row1);
	auto r2 = row(matrix, row2);
	std::ranges::swap(r1, r2);
}

void swap_columns(functor::container auto&& matrix, size_t column1, size_t column2)
{
	auto c1 = column(matrix, column1);
	auto c2 = column(matrix, column2);
	std::ranges::swap(c1, c2);
}

NGS_MATH_MATRIX_END