#pragma once

#include "NGS/math/matrix/concept.h"

NGS_MATH_MATRIX_BEGIN


template<size_t _Order, class _ValueType>
struct identity_matrix : matrix_expression<identity_matrix<_Order, _ValueType>>
{
	NGS_MPL_ENVIRON(identity_matrix);
public:
	constexpr static size_t rows = _Order;
	constexpr static size_t columns = _Order;
	using value_type = _ValueType;
public:
	static constexpr bool VALID(size_t row, size_t column)
	{
		return row == column;
	}
public:
	constexpr identity_matrix() = default;

	constexpr const value_type& access(size_t row, size_t column) const
	{
		return VALID(row,column);
	}
};

NGS_MATH_MATRIX_END