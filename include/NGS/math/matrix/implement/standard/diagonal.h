#pragma once

#include "NGS/math/matrix/concept.h"

NGS_MATH_MATRIX_BEGIN


constexpr bool is_valid_element_in_diagonal(size_t row, size_t column)
{
	return row == column;
}

template<size_t _Order, class _ValueType, class = std::make_index_sequence<_Order>>
struct diagonal_matrix;

template<size_t _Order, class _ValueType, size_t... _Index>
struct diagonal_matrix<_Order, _ValueType, std::index_sequence<_Index...>> : matrix_expression<diagonal_matrix<_Order, _ValueType>>
{
	NGS_MPL_ENVIRON(diagonal_matrix);
public:
	constexpr static size_t rows = _Order;
	constexpr static size_t columns = _Order;
	using value_type = _ValueType;
public:

public:
	constexpr diagonal_matrix() = default;
	constexpr explicit(true) diagonal_matrix(const type_traits::index_type_identity_t<_Index, value_type>&... value) : value(value) {}

	constexpr const value_type& access(size_t row, size_t column) const
	{
		return is_valid_element_in_diagonal(row, column) * value[row];
	}
	constexpr void assign(size_t row, size_t column, const value_type& v)
	{
		NGS_ASSERT_IF_CONSTEVAL(is_valid_element_in_diagonal(row, column), "diagonal_matrix can only assign diagonal elements");
		value[row] = v;
	}
	constexpr void assign(size_t row, size_t column, value_type&& v)
	{
		NGS_ASSERT_IF_CONSTEVAL(is_valid_element_in_diagonal(row, column), "diagonal_matrix can only assign diagonal elements");
		value[row] = std::move(v);
	}
	constexpr self_type& operator=(const self_type& other)
	{
		std::ranges::copy(other.value, std::ranges::begin(value));
		return *this;
	}
public:
	value_type value[rows]{};
};

NGS_MATH_MATRIX_END