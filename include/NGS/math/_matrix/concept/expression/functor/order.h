#pragma once

#include "../../../defined.h"

NGS_MATH_MATRIX_FUNCTOR_BEGIN

inline constexpr size_t invalid_order = -1;

//===============
// row
//===============
template<class>
inline constexpr size_t rows = invalid_order;

template<class _Matrix>
	requires requires{ { type_traits::object_t<_Matrix>::rows } -> std::convertible_to<size_t>; }
inline constexpr size_t rows<_Matrix> = type_traits::object_t<_Matrix>::rows;

template<class _T, class _O = type_traits::object_t<_T>>
concept valid_rows = rows<_O> != invalid_order;

//===============
// column
//===============
template<class>
inline constexpr size_t columns = invalid_order;

template<class _Matrix>
	requires requires{ { type_traits::object_t<_Matrix>::columns } -> std::convertible_to<size_t>; }
inline constexpr size_t columns<_Matrix> = type_traits::object_t<_Matrix>::columns;

template<class _T, class _O = type_traits::object_t<_T>>
concept valid_columns = columns<_O> != invalid_order;

//===============

template<class _T, class _O = type_traits::object_t<_T>>
concept valid_row_column = valid_rows<_T> && valid_columns<_T>;

//===============
// order
//===============
template<class>
inline constexpr size_t order = invalid_order;

template<class _Matrix>
	requires valid_row_column<_Matrix> && (rows<_Matrix> == columns<_Matrix>)
inline constexpr size_t order<_Matrix> = rows<_Matrix>;

template<class _T, class _O = type_traits::object_t<_T>>
concept valid_order = order<_O> != invalid_order;

NGS_MATH_MATRIX_FUNCTOR_END
