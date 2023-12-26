#pragma once

#include "NGS/math/matrix/concept.h"

NGS_MATH_MATRIX_FUNCTOR_BEGIN

template<class _Left, class _Right, size_t _Rows, size_t _Columns, auto _Access>
	requires requires(closure_t<_Left> left, closure_t<_Right> right, size_t row, size_t column) { { _Access(left, right, row, column) }; }
struct binary_functor : yap::expression<binary_functor<_Left, _Right, _Rows, _Columns, _Access>>
{
	constexpr static size_t rows = _Rows;
	constexpr static size_t columns = _Columns;
	constexpr static size_t complexity = yap::complexity<_Left> + yap::complexity<_Right> +1;

	using left_closure_type = closure_t<_Left>;
	using right_closure_type = closure_t<_Right>;

	constexpr binary_functor(closure_param_t<left_closure_type> left, closure_param_t<right_closure_type> right)
		: left(left), right(right)
	{}

	constexpr decltype(auto) access(size_t row, size_t column) const
	{
		return _Access(left, right, row, column);
	}

	left_closure_type left;
	right_closure_type right;
};


NGS_MATH_MATRIX_FUNCTOR_END