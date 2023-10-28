#pragma once

#include "NGS/math/matrix/concept.h"

NGS_MATH_MATRIX_BEGIN
namespace detail {

template<functor::expression _Matrix>
struct row_vector_tag
{
	constexpr static size_t dimension = functor::columns<_Matrix>;

	constexpr static std::pair<size_t, size_t> access(size_t matrix_index, size_t index)
	{
		return { matrix_index,index };
	}
};

template<functor::expression _Matrix>
struct column_vector_tag
{
	constexpr static size_t dimension = functor::rows<_Matrix>;

	constexpr static std::pair<size_t, size_t> access(size_t matrix_index, size_t index)
	{
		return { index,matrix_index };
	}
};

template<functor::expression _Matrix, template<class>class _Type>
struct base_rc_vector : vectors::vector_expression<base_rc_vector<_Matrix, _Type>>
{
	using tag_type = _Type<_Matrix>;
	using range_type = _Matrix;
	constexpr static size_t dimension = tag_type::dimension;

	constexpr base_rc_vector(_Matrix&& matrix, size_t index)
		: _matrix(&matrix)
		, _rc_index(index)
	{}

	constexpr decltype(auto) access(size_t index) const
	{
		auto&& [row, column] = tag_type::access(_rc_index, index);
		return functor::access(*_matrix, row, column);
	}

private:
	type_traits::object_t<range_type>* _matrix;
	size_t _rc_index;
};

template<functor::container _Matrix, template<class>class _Type>
struct base_rc_vector<_Matrix, _Type> : vectors::vector_container<base_rc_vector<_Matrix, _Type>>
{
	NGS_MPL_ENVIRON(base_rc_vector);
public:
	using tag_type = _Type<_Matrix>;
	using range_type = _Matrix;
	constexpr static size_t dimension = tag_type::dimension;
	using value_type = functor::value_t<_Matrix>;

	constexpr base_rc_vector(_Matrix&& matrix, size_t index)
		: _matrix(&matrix)
		, _rc_index(index)
	{}

	using base_type::operator=;
	constexpr decltype(auto) access(size_t index) const
	{
		auto&& [row, column] = tag_type::access(_rc_index, index);
		return functor::access(*_matrix, row, column);
	}

	constexpr decltype(auto) access(size_t index)
	{
		auto&& [row, column] = tag_type::access(_rc_index, index);
		return functor::access(*_matrix, row, column);
	}

	constexpr decltype(auto) assign(size_t index, const value_type& value)
	{
		auto&& [row, column] = tag_type::access(_rc_index, index);
		return functor::assign(*_matrix, row, column, value);
	}
	constexpr decltype(auto) assign(size_t index, vectors::functor::accessible auto&& vector)
	{
		auto&& [row, column] = tag_type::access(_rc_index, index);
		return functor::assign(*_matrix, row, column, vectors::functor::access(NGS_PERFECT_FORWARD(vector), index));
	}
	constexpr decltype(auto) assign(vectors::functor::accessible auto&& vector)
	{
		for (size_t i = 0; i < dimension; i++)
		{
			auto&& [row, column] = tag_type::access(_rc_index, i);
			functor::assign(*_matrix, row, column, vectors::functor::access(NGS_PERFECT_FORWARD(vector), i));
		}
	}
private:
	type_traits::object_t<range_type>* _matrix;
	size_t _rc_index;
};

template<functor::expression _Matrix>
using row_vector = base_rc_vector<_Matrix, row_vector_tag>;

template<functor::expression _Matrix>
using column_vector = base_rc_vector<_Matrix, column_vector_tag>;

}

constexpr decltype(auto) row(functor::expression auto&& matrix, size_t index)
{
	return detail::row_vector<NGS_EXPRESSION_TYPE(matrix)>(NGS_PERFECT_FORWARD(matrix), index);
}

constexpr decltype(auto) column(functor::expression auto&& matrix, size_t index)
{
	return detail::column_vector<NGS_EXPRESSION_TYPE(matrix)>(NGS_PERFECT_FORWARD(matrix), index);
}

NGS_MATH_MATRIX_END