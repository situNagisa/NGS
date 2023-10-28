#pragma once

#include "NGS/math/vector/concept.h"

NGS_MATH_VECTOR_FUNCTOR_BEGIN

template<expression _Left, expression _Right, auto _Access>
	requires dimension_equality<_Left, _Right>&& requires(closure_t<_Left> left, closure_t<_Right> right, size_t index) { { _Access(left, right, index) }; }
struct binary_functor : yap::expression<binary_functor<_Left, _Right, _Access>>
{
	constexpr static size_t dimension = functor::dimension<_Left>;
	constexpr static size_t complexity = yap::complexity<_Left> +yap::complexity<_Right> +1;

	using left_closure_type = closure_t<_Left>;
	using right_closure_type = closure_t<_Right>;

	constexpr binary_functor(closure_param_t<left_closure_type> left, closure_param_t<right_closure_type> right)
		: left(left), right(right)
	{}

	constexpr decltype(auto) access(size_t index) const
	{
		return _Access(left, right, index);
	}

	left_closure_type left;
	right_closure_type right;
};


NGS_MATH_VECTOR_FUNCTOR_END