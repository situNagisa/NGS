#pragma once

#include "NGS/math/matrix/concept.h"
#include "./layout.h"

NGS_MATH_MATRIX_BEGIN

template<
	size_t _Row, size_t _Column,
	class _ValueType,
	template<size_t, size_t>class _Layout = functor::row_tag,
	class = std::make_index_sequence<_Row* _Column>
>
struct matrix;

template<
	size_t  _Row, size_t _Column,
	class _ValueType,
	template<size_t, size_t>class _Layout,
	size_t... _Index>
struct matrix<_Row, _Column, _ValueType, _Layout, std::index_sequence<_Index...>>
	: matrix_container<matrix<_Row, _Column, _ValueType, _Layout>>
{
	static_assert(functor::layout<_Layout<_Row, _Column>>, "layout must be a layout type");

	NGS_MPL_ENVIRON(matrix);
public:
	NGS_MPL_INHERIT_TYPE(expression_type, base_type);
public:
	constexpr static size_t rows = _Row;
	constexpr static size_t columns = _Column;
	using value_type = _ValueType;
	using layout_type = _Layout<rows, columns>;

public:
	using base_type::base_type;
	/**
	 * \brief 默认初始化
	 * \note 此函数用于减缓智能提示压力
	 */
	constexpr matrix() = default;

	constexpr matrix(const type_traits::index_type_identity_t<_Index, value_type>&... values)
		: source{ values... }
	{
		if constexpr (!cpt::naked_same_as<layout_type, functor::row_tag<rows, columns>>)
		{
			std::array<value_type, sizeof...(_Index)> temp{ values... };
			((source[layout_type::standard_sequence(_Index)] = temp[_Index]), ...);
		}
	}
	constexpr explicit(false) matrix(auto&& v)
		requires functor::copyable<expression_type, decltype(v)>
	{
		functor::copy(base_type::_derived(), NGS_PP_PERFECT_FORWARD(v));
	}

	using base_type::operator=;

	constexpr auto&& access(size_t row, size_t column)
	{
		return source[layout_type::transform(row, column)];
	}
	constexpr auto&& access(size_t row, size_t column)const
	{
		return source[layout_type::transform(row, column)];
	}

	constexpr void assign(size_t row, size_t column, functor::accessible auto&& right)
	{
		source[layout_type::transform(row, column)] = static_cast<value_type>(functor::access(NGS_PP_PERFECT_FORWARD(right), row, column));
	}

	/**
	 * \brief 
	 * \param row 
	 * \param column 
	 * \param right
	 * \note 声明此函数是为了减缓智能提示压力
	 */
	constexpr void assign(size_t row,size_t column,const value_type& right){ source[layout_type::transform(row, column)] = static_cast<value_type>(right); }
	constexpr void assign(size_t row, size_t column, std::convertible_to<value_type> auto&& right)
	{
		source[layout_type::transform(row, column)] = static_cast<value_type>(right);
	}
	constexpr void assign(const type_traits::index_type_identity_t<_Index, value_type>&... right)
	{
		((source[layout_type::standard_sequence(_Index)] = right), ...);
	}
	//copy
	constexpr void assign(functor::accessible auto&& right)
	{
		for (size_t i = 0; i < rows * columns; i++)
		{
			auto&& [row, column] = layout_type::transform(i);
			source[layout_type::standard_sequence(i)] = static_cast<value_type>(functor::access(NGS_PP_PERFECT_FORWARD(right), row, column));
		}
	}
public:
	value_type source[rows * columns]{};
};

#define _NGS_DECLARE_MATRIX(row,column)														\
template<class _ValueType> using matrix##row##x##column = matrix<row, column, _ValueType>;	\
using matrix##row##x##column##f = matrix##row##x##column<float>;							\
using matrix##row##x##column##d = matrix##row##x##column<double>;							\
using matrix##row##x##column##i = matrix##row##x##column<int>;								\
using matrix##row##x##column##u = matrix##row##x##column<unsigned int>;						\
using matrix##row##x##column##s = matrix##row##x##column<size_t>							\
//


_NGS_DECLARE_MATRIX(1, 1);
_NGS_DECLARE_MATRIX(1, 2);
_NGS_DECLARE_MATRIX(1, 3);
_NGS_DECLARE_MATRIX(1, 4);

_NGS_DECLARE_MATRIX(2, 1);
_NGS_DECLARE_MATRIX(2, 2);
_NGS_DECLARE_MATRIX(2, 3);
_NGS_DECLARE_MATRIX(2, 4);

_NGS_DECLARE_MATRIX(3, 1);
_NGS_DECLARE_MATRIX(3, 2);
_NGS_DECLARE_MATRIX(3, 3);
_NGS_DECLARE_MATRIX(3, 4);

_NGS_DECLARE_MATRIX(4, 1);
_NGS_DECLARE_MATRIX(4, 2);
_NGS_DECLARE_MATRIX(4, 3);
_NGS_DECLARE_MATRIX(4, 4);

#undef _NGS_DECLARE_MATRIX



NGS_MATH_MATRIX_END