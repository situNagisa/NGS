#pragma once

#include "../expression.h"

NGS_MATH_VECTOR_FUNCTOR_BEGIN

template<class _L,class _R = _L>
concept normable = requires(_L l,_R r){ { sqrt((l * r) + (l * r)) }; };
template<class _L,class _R = _L>
	requires normable<_L,_R>
using norm_t = type_traits::naked_t<decltype(sqrt(declval<type_traits::add_t<type_traits::multiply_t<_L,_R>>>()))>;

NGS_MATH_VECTOR_FUNCTOR_END

NGS_MATH_VECTOR_BEGIN

template<functor::expression _Vector>
	requires functor::normable<functor::vector_value_t<_Vector>>
constexpr auto norm_squared(_Vector&& expr) {
	using value_type = functor::vector_value_t<_Vector>;
	value_type result{};
	for (size_t i = 0; i < functor::dimension<_Vector>; i++)
	{
		result += functor::access(NGS_PERFECT_FORWARD(expr), i) * functor::access(NGS_PERFECT_FORWARD(expr), i);
	}
	return result;
}
template<functor::expression _Vector>
constexpr auto norm(_Vector&& expr) { return sqrt(norm_squared(NGS_PERFECT_FORWARD(expr))); }


NGS_MATH_VECTOR_END