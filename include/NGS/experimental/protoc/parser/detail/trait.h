#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(create_context, (concepts::any));
NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(check, (concepts::any, concepts::any));
NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(parse, (concepts::any, concepts::any));
NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(_lose, (concepts::any, concepts::any));
inline constexpr struct
{
	constexpr NGS_CONFIG_STATIC_CALL_OPERATOR decltype(auto) operator()(auto&& target, auto&& buffer, auto&& context) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		if constexpr (::std::invocable<decltype(_lose),decltype(target), decltype(buffer), decltype(context)>)
		{
			return _lose(NGS_PP_PERFECT_FORWARD(target), NGS_PP_PERFECT_FORWARD(buffer), NGS_PP_PERFECT_FORWARD(context));
		}
		else
		{
			return 0u;
		}
	}
}lose{};


NGS_LIB_MODULE_END