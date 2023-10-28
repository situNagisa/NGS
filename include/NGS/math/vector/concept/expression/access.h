#pragma once

#include "../../defined.h"

NGS_MATH_VECTOR_BEGIN
//constexpr auto access(cpt::none auto&&,size_t){}
NGS_MATH_VECTOR_END

NGS_MATH_VECTOR_FUNCTOR_BEGIN

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
		square_bracket,
	};
	template<class _Type, NGS_CONSTEXPR_CLEAR_BUFFER>
	constexpr static auto CHOICE()
	{
		if constexpr (requires(_Type expr, size_t index) { { access(NGS_PERFECT_FORWARD(expr), index) }; })
		{
			return choice_type::global;
		}
		else if constexpr (requires(_Type expr, size_t index) { { expr.access(index) }; })
		{
			return choice_type::member;
		}
		else if constexpr (requires(_Type expr, size_t index) { { expr(index) }; })
		{
			return choice_type::round_bracket;
		}
		else if constexpr (requires(_Type expr, size_t index) { { expr[index] }; })
		{
			return choice_type::square_bracket;
		}
		else
		{
			return choice_type::none;
		}
	}

	constexpr decltype(auto) operator()(auto&& expression, size_t index) const
		requires (CHOICE<decltype(expression)>() == choice_type::global)
	{
		return access(NGS_PERFECT_FORWARD(expression), index);
	}
	constexpr decltype(auto) operator()(auto&& expression, size_t index) const
		requires (CHOICE<decltype(expression)>() == choice_type::member)
	{
		return expression.access(index);
	}
	constexpr decltype(auto) operator()(auto&& expression, size_t index) const
		requires (CHOICE<decltype(expression)>() == choice_type::round_bracket)
	{
		return expression(index);
	}
	constexpr decltype(auto) operator()(auto&& expression, size_t index) const
		requires (CHOICE<decltype(expression)>() == choice_type::square_bracket)
	{
		return expression[index];
	}
} access{};

}

using detail::access;

template<class _T, class _O = type_traits::object_t<_T>>
concept accessible = requires(_T expr, size_t index)
{
	{ detail::access(expr, index) };
};

NGS_MATH_VECTOR_FUNCTOR_END
