#pragma once

#include "../norm.h"
#include "./arithmetic.h"

NGS_MATH_LA_VECTOR_VIEW_BEGIN

inline constexpr struct
{
	constexpr decltype(auto) operator()(concepts::vectors::normable auto&& expr) const
		requires cpt::divisible<traits::vectors::value_t<decltype(expr)>, traits::vectors::norm_t<decltype(expr)>>
	{
		using value_type = type_traits::divide_t<traits::vectors::value_t<decltype(expr)>, traits::vectors::norm_t<decltype(expr)>>;
		using vector_type = containers::vectors::vector<adapters::vectors::static_dimension<decltype(expr)>, value_type >;
		vector_type result{};
		for (traits::vectors::index_t i = 0; i < adapters::vectors::dimension(expr); i++)
		{
			adapters::vectors::assign(result, i, adapters::vectors::access(expr, i) / vectors::norm(expr));
		}
		return result;
	}
}normalize{};

NGS_MATH_LA_VECTOR_VIEW_END