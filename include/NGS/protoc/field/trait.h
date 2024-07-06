#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

inline constexpr struct
{
	enum class choose_type
	{
		none,
		member,
		callable,
		adl,
	};

	template<class T, class R>
	consteval static auto choose()
	{
		if constexpr (requires(T t, R r) { NGS_PP_PERFECT_FORWARD(t).check(NGS_PP_PERFECT_FORWARD(r)); })
		{
			return choose_type::member;
		}
		else if constexpr (requires(T t, R r) { NGS_PP_PERFECT_FORWARD(t)(NGS_PP_PERFECT_FORWARD(r)); })
		{
			return choose_type::callable;
		}
		else if constexpr (requires(T t, R r) { check(NGS_PP_PERFECT_FORWARD(t), NGS_PP_PERFECT_FORWARD(r)); })
		{
			return choose_type::adl;
		}
		else
		{
			return choose_type::none;
		}
	}

	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(auto&& t, ::std::ranges::input_range auto&& r) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
		requires (choose<decltype(t), decltype(r)>() != choose_type::none)
	{
		constexpr auto chose = choose<decltype(t), decltype(r)>();
		if constexpr (chose == choose_type::member)
		{
			return NGS_PP_PERFECT_FORWARD(t).check(NGS_PP_PERFECT_FORWARD(r));
		}
		else if constexpr (chose == choose_type::callable)
		{
			return NGS_PP_PERFECT_FORWARD(t)(NGS_PP_PERFECT_FORWARD(r));
		}
		else if constexpr (chose == choose_type::adl)
		{
			return check(NGS_PP_PERFECT_FORWARD(t), NGS_PP_PERFECT_FORWARD(r));
		}
	}
}check{};


NGS_LIB_MODULE_END