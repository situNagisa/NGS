#pragma once

#include "NGS/math/matrix/concept.h"

NGS_MATH_MATRIX_FUNCTOR_BEGIN

template<class _T, class _O = type_traits::object_t<_T>>
concept layout = requires(size_t index, size_t row, size_t column)
{
	{ _O::transform(row, column)} -> std::convertible_to<size_t>;
	{ _O::transform(index) };//structured binding @code
	//以row主序的标准序列
	{ _O::standard_sequence(index) } -> std::convertible_to<size_t>;
};

template<size_t _Rows, size_t _Columns>
struct row_tag
{
	constexpr static size_t rows = _Rows;
	constexpr static size_t columns = _Columns;

	constexpr static size_t transform(size_t row, size_t column)
	{
		return row * columns + column;
	}
	constexpr static std::pair<size_t, size_t> transform(size_t index)
	{
		return { index / columns, index % columns };
	}
	constexpr static size_t standard_sequence(size_t index)
	{
		return index;
	}
};

template<size_t _Rows, size_t _Columns>
struct column_tag
{
	constexpr static size_t rows = _Rows;
	constexpr static size_t columns = _Columns;

	constexpr static size_t transform(size_t row, size_t column)
	{
		return column * rows + row;
	}
	constexpr static std::pair<size_t, size_t> transform(size_t index)
	{
		return { index % rows, index / rows };
	}
	constexpr static size_t standard_sequence(size_t index)
	{
		const size_t quotients = index / columns;
		return index * rows + (1 - rows * columns) * quotients;
	}
};

NGS_MATH_MATRIX_FUNCTOR_END