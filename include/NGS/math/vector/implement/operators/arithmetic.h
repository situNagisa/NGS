#pragma once

#include "NGS/math/vector/concept.h"
#include "../standard/scalar.h"
#include "../standard/binary.h"

NGS_MATH_VECTOR_BEGIN

namespace detail_arithmetic {

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
			requires functor::dimension_equality<_Left, _Right>;
			requires _Concept<functor::value_t<_Left>, functor::value_t<_Right>>::value;
		})
		{
			return choice_type::expression;
		}
		else if constexpr (requires
		{
			requires functor::expression<_Left>;
			requires !matrixes::functor::expression<_Right>;
			requires _Concept<functor::value_t<_Left>, _Right>::value;
		})
		{
			return choice_type::expr_value;
		}
		else if constexpr (requires
		{
			requires !matrixes::functor::expression<_Left>;
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
	struct arithmetic_functor
	{
		constexpr decltype(auto) operator()(auto&& left, auto&& right) const
			requires (choice<decltype(left), decltype(right), _Concept>() == choice_type::expression)
		{
			return functor::binary_functor<decltype((left)), decltype((right)), _Access>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
		}
		constexpr decltype(auto) operator()(auto&& left, auto&& right) const
			requires (choice<decltype(left), decltype(right), _Concept>() == choice_type::value_expr)
		{
			using adapter_type = scalar_adapter<functor::dimension<decltype(right)>, type_traits::object_t<decltype(left)>>;

			return (*this)(adapter_type(NGS_PP_PERFECT_FORWARD(left)), NGS_PP_PERFECT_FORWARD(right));
		}
		constexpr decltype(auto) operator()(auto&& left, auto&& right) const
			requires (choice<decltype(left), decltype(right), _Concept>() == choice_type::expr_value)
		{
			using adapter_type = scalar_adapter<functor::dimension<decltype(left)>, type_traits::object_t<decltype(right)>>;

			return (*this)(NGS_PP_PERFECT_FORWARD(left), adapter_type(NGS_PP_PERFECT_FORWARD(right)));
		}
	};

	inline constexpr auto add = arithmetic_functor < type_traits::is_addable, [](auto&& left, auto&& right, size_t index)
		{
			return functor::access(NGS_PP_PERFECT_FORWARD(left), index) + functor::access(NGS_PP_PERFECT_FORWARD(right), index);
		} > {};
		inline constexpr auto subtract = arithmetic_functor < type_traits::is_subtractable, [](auto&& left, auto&& right, size_t index)
			{
				return functor::access(NGS_PP_PERFECT_FORWARD(left), index) - functor::access(NGS_PP_PERFECT_FORWARD(right), index);
			} > {};
			inline constexpr auto multiply = arithmetic_functor < type_traits::is_multipliable, [](auto&& left, auto&& right, size_t index)
				{
					return functor::access(NGS_PP_PERFECT_FORWARD(left), index) * functor::access(NGS_PP_PERFECT_FORWARD(right), index);
				} > {};
				inline constexpr auto divide = arithmetic_functor < type_traits::is_divisible, [](auto&& left, auto&& right, size_t index)
					{
						return functor::access(NGS_PP_PERFECT_FORWARD(left), index) / functor::access(NGS_PP_PERFECT_FORWARD(right), index);
					} > {};

}

using detail_arithmetic::add;
using detail_arithmetic::subtract;
using detail_arithmetic::multiply;
using detail_arithmetic::divide;

constexpr decltype(auto) operator+(auto&& left, auto&& right)
	requires requires{ detail_arithmetic::add(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)); }
{
	return  detail_arithmetic::add(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

constexpr decltype(auto) operator-(auto&& left, auto&& right)
	requires requires { detail_arithmetic::subtract(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)); }
{
	return  detail_arithmetic::subtract(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

constexpr decltype(auto) operator*(auto&& left, auto&& right)
	requires requires { detail_arithmetic::multiply(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)); }
{
	return  detail_arithmetic::multiply(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

constexpr decltype(auto) operator/(auto&& left, auto&& right)
	requires requires { divide(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)); }
{
	return  detail_arithmetic::divide(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

//using detail_arithmetic::add;

NGS_MATH_VECTOR_END