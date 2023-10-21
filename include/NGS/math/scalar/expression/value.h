#pragma once

#include "./concept.h"

NGS_MATH_SCALAR_BEGIN

namespace detail
{
struct value_function_impl
{
	constexpr auto operator()(CScalarExpression auto&& expression) const -> decltype(expression.value())
		requires requires{ { expression.value() }; }
	{
		return expression.value();
	}
};

inline constexpr value_function_impl value{};
}

using detail::value;

NGS_MATH_SCALAR_END
