#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_BEGIN

constexpr void for_each(tuple_like auto&& tuple,/*::std::invocable<decltype(tuple)>*/ auto&& unary_function)
{
	::std::apply([&](auto&&... args) { (unary_function(NGS_PP_PERFECT_FORWARD(args)),...); }, NGS_PP_PERFECT_FORWARD(tuple));
}


NGS_LIB_END