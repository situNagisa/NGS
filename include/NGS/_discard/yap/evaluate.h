#pragma once

#include "./concept.h"

NGS_YAP_BEGIN

namespace detail
{
	struct evaluate_function_impl
	{
		constexpr auto&& operator()(CExpression auto&& expression) const
		{
			if constexpr (requires{ expression.evaluate(); })
			{
				return expression.evaluate();
			}
			else
			{
				return std::forward<decltype(expression)>(expression);
			}
		}
	};

	inline constexpr evaluate_function_impl evaluate{};
}

using detail::evaluate;

NGS_YAP_END
