#pragma once

#include "../../../defined.h"

NGS_MATH_MATRIX_BEGIN
//constexpr auto access(cpt::none auto&&, size_t, size_t) {}
NGS_MATH_MATRIX_END

NGS_MATH_MATRIX_FUNCTOR_BEGIN

namespace detail
{
inline constexpr struct
{
	enum class choice_type
	{
		none,
		global,
		member,
		round_bracket,
	};
	template<class _Type, NGS_PP_CONSTEXPR_CLEAR_BUFFER>
	constexpr static auto CHOICE()
	{
		if constexpr (requires(_Type expr, size_t row, size_t column) { { access(NGS_PP_PERFECT_FORWARD(expr), row, column) }; })
		{
			return choice_type::global;
		}
		else if constexpr (requires(_Type expr, size_t row, size_t column) { { expr.access(row, column) }; })
		{
			return choice_type::member;
		}
		else if constexpr (requires(_Type expr, size_t row, size_t column) { { expr(row, column) }; })
		{
			return choice_type::round_bracket;
		}
		else
		{
			return choice_type::none;
		}
	}

	constexpr decltype(auto) operator()(auto&& expression, size_t row, size_t column) const
		requires (CHOICE<decltype(expression)>() == choice_type::global)
	{
		return access(NGS_PP_PERFECT_FORWARD(expression), row, column);
	}
	constexpr decltype(auto) operator()(auto&& expression, size_t row, size_t column) const
		requires (CHOICE<decltype(expression)>() == choice_type::member)
	{
		return expression.access(row, column);
	}
	constexpr decltype(auto) operator()(auto&& expression, size_t row, size_t column) const
		requires (CHOICE<decltype(expression)>() == choice_type::round_bracket)
	{
		return expression(row, column);
	}
} access{};

}

using detail::access;

template<class _T, class _O = type_traits::object_t<_T>>
concept accessible = requires(_T expr, size_t row, size_t column)
{
	{ detail::access(expr, row, column) };
};

NGS_MATH_MATRIX_FUNCTOR_END
