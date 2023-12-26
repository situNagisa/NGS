#pragma once

#include "./diagonal.h"

NGS_MATH_MATRIX_BEGIN

template<size_t _Order, class _ValueType>
struct quantity_matrix : matrix_expression<quantity_matrix<_Order, _ValueType>>
{
	constexpr static size_t rows = _Order;
	constexpr static size_t columns = _Order;
	using value_type = _ValueType;

	constexpr quantity_matrix() = default;
	constexpr explicit(true) quantity_matrix(const value_type& value) : value(value) {}

	constexpr const value_type& access(size_t row, size_t column) const
	{
		return is_valid_element_in_diagonal(row,column) * value;
	}
public:
	value_type value{};
};

NGS_MATH_MATRIX_END