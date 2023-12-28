#pragma once

#include "NGS/math/matrix/concept.h"

NGS_MATH_MATRIX_BEGIN

template<size_t _Order, class _ValueType>
struct zero_matrix : matrix_expression<zero_matrix<_Order, _ValueType>>
{
	NGS_MPL_ENVIRON(zero_matrix);
public:
	constexpr static size_t rows = _Order;
	constexpr static size_t columns = _Order;
	using value_type = _ValueType;
public:
	constexpr zero_matrix() = default;

	constexpr const value_type& access(size_t row, size_t column) const
	{
		return value_type{};
	}
};

NGS_MATH_MATRIX_END