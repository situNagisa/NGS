#pragma once

#include "NGS/math/matrix/concept.h"

NGS_MATH_MATRIX_BEGIN

template<size_t _Row,size_t _Column, class _ValueType>
struct trivial_matrix : matrix_expression<trivial_matrix<_Row,_Column,_ValueType>>
{
	constexpr static size_t rows = _Row;
	constexpr static size_t columns = _Column;
	using value_type = _ValueType;

	constexpr trivial_matrix() = default;
	constexpr explicit(true) trivial_matrix(const value_type& value) : value(value) {}

	constexpr const value_type& access(size_t row, size_t column) const
	{
		return value;
	}
public:
	value_type value{};
};

NGS_MATH_MATRIX_END