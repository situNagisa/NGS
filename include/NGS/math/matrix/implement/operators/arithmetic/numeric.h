#pragma once

#include "../../standard/binary.h"
#include "../../standard/trivial.h"

NGS_MATH_MATRIX_FUNCTOR_BEGIN

//template<class _L, class _R,
//	class _M = std::conditional_t<expression<_L>,_L,_R>,
//	class _N = std::conditional_t<expression<_L>,_R,_L>
//>
//concept multipliable_with_number = requires(_M matrix, _N number, size_t row_index, size_t col_index)
//{
//	requires expression<_M>;
//	requires !expression<_N> && !vectors::functor::expression<_N>;
//	requires cpt::multipliable<value_t<_M>, _N>;
//};

NGS_MATH_MATRIX_FUNCTOR_END

NGS_MATH_MATRIX_BEGIN  namespace detail_arithmetic {

enum class choice_type
{
	none,
	expression,
	value_expr,
	expr_value,
};
template<class _Left, class _Right, template<class, class>class _Concept>
constexpr auto choice()
{
	if constexpr (requires
	{
		requires functor::expression<_Left>;
		requires functor::expression<_Right>;
		requires functor::same_type<_Left, _Right>;
		requires _Concept<functor::value_t<_Left>, functor::value_t<_Right>>::value;
	})
	{
		return choice_type::expression;
	}
	else if constexpr (requires
	{
		requires functor::expression<_Left>;
		requires _Concept<functor::value_t<_Left>, _Right>::value;
	})
	{
		return choice_type::expr_value;
	}
	else if constexpr (requires
	{
		requires functor::expression<_Right>;
		requires _Concept<_Left, functor::value_t<_Right>>::value;
	})
	{
		return choice_type::value_expr;
	}
	else
	{
		return choice_type::none;
	}
}

template<template<class, class>class _Concept, auto _Access>
struct numeric_functor
{
	constexpr decltype(auto) operator()(auto&& left, auto&& right) const
		requires (choice<decltype(left), decltype(right), _Concept>() == choice_type::expression)
	{
		return functor::binary_functor<decltype(left), decltype(right),functor::rows<decltype(left)>,functor::columns<decltype(left)>, _Access>{NGS_PERFECT_FORWARD(left), NGS_PERFECT_FORWARD(right)};
	}
	constexpr decltype(auto) operator()(auto&& left, auto&& right) const
		requires (choice<decltype(left), decltype(right), _Concept>() == choice_type::value_expr)
	{
		using adapter_type = trivial_matrix<functor::rows<decltype(left)>, functor::columns<decltype(left)>, type_traits::object_t<decltype(left)>>;

		return (*this)(adapter_type(NGS_PERFECT_FORWARD(left)), NGS_PERFECT_FORWARD(right));
	}
	constexpr decltype(auto) operator()(auto&& left, auto&& right) const
		requires (choice<decltype(left), decltype(right), _Concept>() == choice_type::expr_value)
	{
		using adapter_type = trivial_matrix<functor::rows<decltype(left)>, functor::columns<decltype(left)>, type_traits::object_t<decltype(right)>>;

		return (*this)(NGS_PERFECT_FORWARD(left), adapter_type(NGS_PERFECT_FORWARD(right)));
	}
};

inline constexpr auto add = numeric_functor < type_traits::is_addable, [](auto&& left, auto&& right,size_t row,size_t column) -> decltype(auto) {
	return functor::access(NGS_PERFECT_FORWARD(left), row, column) + functor::access(NGS_PERFECT_FORWARD(right), row, column);
} > ();

inline constexpr auto subtract = numeric_functor < type_traits::is_subtractable, [](auto&& left, auto&& right,size_t row,size_t column) -> decltype(auto) {
	return functor::access(NGS_PERFECT_FORWARD(left), row, column) - functor::access(NGS_PERFECT_FORWARD(right), row, column);
} > ();

//inline constexpr auto multiply_numeric = numeric_functor < type_traits::is_multipliable, [](auto&& left, auto&& right,size_t row,size_t column) -> decltype(auto) {
//	return functor::access(NGS_PERFECT_FORWARD(left), row, column) * functor::access(NGS_PERFECT_FORWARD(right), row, column);
//} > ();

inline constexpr auto divide_numeric = numeric_functor < type_traits::is_divisible, [](auto&& left, auto&& right,size_t row,size_t column) -> decltype(auto) {
	return functor::access(NGS_PERFECT_FORWARD(left), row, column) / functor::access(NGS_PERFECT_FORWARD(right), row, column);
} > ();

}

using detail_arithmetic::add;
using detail_arithmetic::subtract;
//using detail_arithmetic::multiply_numeric;
using detail_arithmetic::divide_numeric;

NGS_MATH_MATRIX_END