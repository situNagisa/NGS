#pragma once

#include "../defined.h"

NGS_MATH_VECTOR_BEGIN
constexpr auto copy(cpt::none auto&&, cpt::none auto&) {}
NGS_MATH_VECTOR_END

NGS_MATH_VECTOR_FUNCTOR_BEGIN

namespace detail
{
inline constexpr struct copy_function_impl
{
	enum class choice_type
	{
		none,
		global,
		member,
		operate,
	};
	template<class _Left, class _Right, NGS_CONSTEXPR_CLEAR_BUFFER>
	constexpr static auto CHOICE()
	{
		if constexpr (
			requires(_Left left, _Right right) { { copy(NGS_PERFECT_FORWARD(left), NGS_PERFECT_FORWARD(right)) }; }
		) {
			return choice_type::global;
		}
		else if constexpr (
			requires(_Left left, _Right right) { { left.assign(NGS_PERFECT_FORWARD(right)) }; }
		) {
			return choice_type::member;
		}
		else if constexpr (
			requires(_Left left, _Right right) { { left = NGS_PERFECT_FORWARD(right) }; }
		)
		{
			return choice_type::operate;
		}
		else
		{
			return choice_type::none;
		}
	}

	constexpr decltype(auto) operator()(auto&& to, auto&& from) const
		requires (CHOICE<decltype(to),decltype(from)>() == choice_type::global)
	{
		return copy(NGS_PERFECT_FORWARD(to), NGS_PERFECT_FORWARD(from));
	}
	constexpr decltype(auto) operator()(auto&& to, auto&& from) const
		requires (CHOICE<decltype(to),decltype(from)>() == choice_type::member)
	{
		return to.assign(NGS_PERFECT_FORWARD(from));
	}
	constexpr decltype(auto) operator()(auto&& to, auto&& from) const
		requires (CHOICE<decltype(to),decltype(from)>() == choice_type::operate)
	{
		return to = NGS_PERFECT_FORWARD(from);
	}
} copy{};

}

using detail::copy;

template<class _Left, class _Right>
concept copyable = requires(_Left left, _Right right)
{
	{ detail::copy(NGS_PERFECT_FORWARD(left), NGS_PERFECT_FORWARD(right)) };
};

NGS_MATH_VECTOR_FUNCTOR_END
