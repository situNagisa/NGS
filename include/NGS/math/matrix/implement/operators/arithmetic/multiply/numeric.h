#pragma once

#include "../../access.h"

NGS_MATH_MATRIX_FUNCTOR_BEGIN

template<class _M, class _N>
concept left_multipliable_with_number = requires(_M matrix, _N number, size_t row_index, size_t col_index)
{
	requires expression<_M>;
	requires !expression<_N> && !vectors::functor::expression<_N>;
	requires cpt::multipliable<value_t<_M>, _N>;
};

template<class _N, class _M>
concept right_multipliable_with_number = requires(_M matrix, _N number, size_t row_index, size_t col_index)
{
	requires expression<_M>;
	requires !expression<_N> && !vectors::functor::expression<_N>;
	requires cpt::multipliable<_N, value_t<_M>>;
};

template<class _L, class _R>
concept multipliable_with_number = left_multipliable_with_number<_L, _R> || right_multipliable_with_number<_L, _R>;

NGS_MATH_MATRIX_FUNCTOR_END

NGS_MATH_MATRIX_BEGIN  namespace detail_arithmetic {

template<class _Matrix, class _Number>
	requires functor::left_multipliable_with_number<_Matrix, _Number>
struct left_multiply_with_number_function_impl : matrix_expression<left_multiply_with_number_function_impl<_Matrix, _Number>>
{
	using matrix_closure_type = functor::closure_t<_Matrix>;
	using vector_closure_type = _Number;
	constexpr static size_t rows = functor::rows<_Matrix>;
	constexpr static size_t columns = functor::columns<_Matrix>;

	constexpr left_multiply_with_number_function_impl(functor::closure_param_t<_Matrix> matrix, const _Number& number) noexcept
		: matrix(matrix), number(number)
	{}

	constexpr decltype(auto) access(size_t row,size_t column) const
	{
		return functor::access(matrix,row,column) * number;
	}

	matrix_closure_type matrix;
	vector_closure_type number;
};

template<class _Number,class _Matrix>
	requires functor::right_multipliable_with_number<_Number, _Matrix>
struct right_multiply_with_number_function_impl : matrix_expression<right_multiply_with_number_function_impl<_Number, _Matrix>>
{
	using matrix_closure_type = functor::closure_t<_Matrix>;
	using vector_closure_type = _Number;
	constexpr static size_t rows = functor::rows<_Matrix>;
	constexpr static size_t columns = functor::columns<_Matrix>;

	constexpr right_multiply_with_number_function_impl(const _Number& number, functor::closure_param_t<_Matrix> matrix) noexcept
		: matrix(matrix), number(number)
	{}

	constexpr decltype(auto) access(size_t row, size_t column) const
	{
		return number * functor::access(matrix, row, column);
	}

	matrix_closure_type matrix;
	vector_closure_type number;
};


inline constexpr struct
{
	constexpr decltype(auto) operator()(auto&& left, auto&& right) const
		requires functor::left_multipliable_with_number<decltype(left), decltype(right)>
	{
		return left_multiply_with_number_function_impl<decltype(left), decltype(right)>(NGS_PERFECT_FORWARD(left), NGS_PERFECT_FORWARD(right));
	}
	constexpr decltype(auto) operator()(auto&& left, auto&& right) const
		requires functor::right_multipliable_with_number<decltype(left), decltype(right)>
	{
		return right_multiply_with_number_function_impl<decltype(left), decltype(right)>(NGS_PERFECT_FORWARD(left), NGS_PERFECT_FORWARD(right));
	}
}multiply_number;

}

using detail_arithmetic::multiply_number;


NGS_MATH_MATRIX_END