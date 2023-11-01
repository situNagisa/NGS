#pragma once

#include "../../access.h"

NGS_MATH_MATRIX_FUNCTOR_BEGIN

template<class _M, class _V>
concept left_multipliable_with_vector = requires(_M matrix, _V vector, size_t row_index, size_t col_index)
{
	requires expression<_M>;
	requires vectors::functor::expression<_V>;
	{ row(NGS_PP_PERFECT_FORWARD(matrix), row_index) } -> vectors::functor::expression;
	requires vectors::functor::inner_productable<decltype(row(NGS_PP_PERFECT_FORWARD(matrix), row_index)), _V>;
};

template<class _V, class _M>
concept right_multipliable_with_vector = requires(_M matrix, _V vector, size_t row_index, size_t col_index)
{
	requires expression<_M>;
	requires vectors::functor::expression<_V>;
	{ column(NGS_PP_PERFECT_FORWARD(matrix), col_index) } -> vectors::functor::expression;
	requires vectors::functor::inner_productable<_V,decltype(column(NGS_PP_PERFECT_FORWARD(matrix), col_index))>;
};

template<class _L, class _R>
concept multipliable_with_vector = left_multipliable_with_vector<_L, _R> || right_multipliable_with_vector<_L, _R>;

NGS_MATH_MATRIX_FUNCTOR_END

NGS_MATH_MATRIX_BEGIN  namespace detail_arithmetic {

template<class _Matrix,class _Vector>
	requires functor::left_multipliable_with_vector<_Matrix, _Vector>
struct left_multiply_with_vector_function_impl : vectors::vector_expression<left_multiply_with_vector_function_impl<_Matrix,_Vector>>
{
	using matrix_closure_type = functor::closure_t<_Matrix>;
	using vector_closure_type = vectors::functor::closure_t<_Vector>;
	constexpr static size_t dimension = vectors::functor::dimension<_Vector>;

	constexpr left_multiply_with_vector_function_impl(functor::closure_param_t<_Matrix> matrix, vectors::functor::closure_param_t<_Vector> vector) noexcept
		: matrix(matrix), vector(vector)
	{}

	constexpr decltype(auto) access(size_t index) const
	{
		return vectors::product_inner(row(matrix, index), vector);
	}

	matrix_closure_type matrix;
	vector_closure_type vector;
};

template<class _Vector,class _Matrix>
	requires functor::right_multipliable_with_vector<_Vector,_Matrix>
struct right_multiply_with_vector_function_impl : vectors::vector_expression<right_multiply_with_vector_function_impl<_Vector,_Matrix>>
{
	using matrix_closure_type = functor::closure_t<_Matrix>;
	using vector_closure_type = vectors::functor::closure_t<_Vector>;
	constexpr static size_t dimension = vectors::functor::dimension<_Vector>;

	constexpr right_multiply_with_vector_function_impl(vectors::functor::closure_param_t<_Vector> vector, functor::closure_param_t<_Matrix> matrix) noexcept
		: matrix(matrix), vector(vector)
	{}

	constexpr decltype(auto) access(size_t index) const
	{
		return vectors::product_inner(vector, column(matrix, index));
	}

	matrix_closure_type matrix;
	vector_closure_type vector;
};

inline constexpr struct
{
	constexpr decltype(auto) operator()(auto&& left, auto&& right) const
		requires functor::left_multipliable_with_vector<decltype(left), decltype(right)>
	{
		return left_multiply_with_vector_function_impl<decltype(left),decltype(right)>(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
	}
	constexpr decltype(auto) operator()(auto&& left, auto&& right) const
		requires functor::right_multipliable_with_vector<decltype(left), decltype(right)>
	{
		return right_multiply_with_vector_function_impl<decltype(left),decltype(right)>(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
	}
}multiply_vector;

}

using detail_arithmetic::multiply_vector;


NGS_MATH_MATRIX_END