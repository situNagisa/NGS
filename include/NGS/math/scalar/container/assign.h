#pragma once

#include "./concept.h"
#include "../expression/value_type.h"

NGS_MATH_SCALAR_BEGIN

namespace detail
{
struct assign_function_impl
{
	constexpr auto operator()(CScalarContainer auto& left, CScalarExpression auto&& right) const
		requires requires{ { left.assign(NGS_PP_PERFECT_FORWARD(right)) }; }
	{
		using left_type = meta::scalar_value_t<decltype(left)>;
		using right_type = meta::scalar_value_t<decltype(right)>;

		return left.assign(
			static_cast<type_traits::add_cvref_like_t<right_type, left_type>>(
				static_cast<right_type>(NGS_PP_PERFECT_FORWARD(right))
				)
		);
	}

	constexpr auto operator()(CScalarContainer auto& left, auto&& right) const
		requires type_traits::is_same_object_v<meta::scalar_value_t<decltype(left)>, decltype(right)>&& requires{ { left.assign(NGS_PP_PERFECT_FORWARD(right)) }; }
	{
		return left.assign(NGS_PP_PERFECT_FORWARD(right));
	}
};

inline constexpr assign_function_impl assign{};
}

using detail::assign;

NGS_MATH_SCALAR_END
