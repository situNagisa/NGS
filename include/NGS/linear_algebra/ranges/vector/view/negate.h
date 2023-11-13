#pragma once

#include "./defined.h"

NGS_MATH_LA_VECTOR_VIEW_BEGIN

inline constexpr struct
{
	template<class _T>
	struct view : containers::vectors::vector_expression<view<_T>>
	{
		constexpr static traits::vectors::dimension_t dimension = adapters::vectors::static_dimension<_T>;

		using closure_type = traits::vectors::closure_t<_T>;
		using closure_param_type = traits::vectors::closure_param_t<_T>;

		constexpr view(closure_param_type vector)
			: closure(vector)
		{}

		constexpr decltype(auto) access(traits::vectors::index_t index)
		{
			return -adapters::vectors::access(closure, index);
		}
		constexpr decltype(auto) access(traits::vectors::index_t index) const
		{
			return -adapters::vectors::access(closure, index);
		}

		closure_type closure;
	};

	constexpr decltype(auto) operator()(concepts::vectors::expression auto&& vector) const
		requires cpt::negativable<traits::vectors::value_t<decltype(vector)>>
	{
		return view<decltype(vector)>(vector);
	}

}negate{};

NGS_MATH_LA_VECTOR_VIEW_END
