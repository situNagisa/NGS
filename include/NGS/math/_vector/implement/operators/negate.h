#pragma once

#include "NGS/math/vector/concept.h"

NGS_MATH_VECTOR_BEGIN

namespace detail
{

template<functor::expression _Vector>
struct negate_function_impl : yap::expression<negate_function_impl<_Vector>>
{
	using closure_type = functor::closure_t<_Vector>;

	constexpr static size_t dimension = functor::dimension<_Vector>;
	constexpr static size_t complexity = yap::complexity<_Vector> +1;

	constexpr negate_function_impl(closure_type closure) : closure(closure) {}

	constexpr auto access(size_t index) const { return -functor::access(closure, index); }

	closure_type closure;
};

}

template<functor::expression _Expression>
constexpr auto negate(_Expression&& expr) { return detail::negate_function_impl<_Expression>(NGS_PP_PERFECT_FORWARD(expr)); }
template<functor::expression _Expression>
constexpr auto operator-(_Expression&& expr) { return negate(NGS_PP_PERFECT_FORWARD(expr)); }

NGS_MATH_VECTOR_END