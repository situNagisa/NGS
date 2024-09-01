#pragma once

#include "./trait.h"
#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr decltype(auto) as_std(tuple auto&& t) noexcept
{
	using tuple_type = ::std::remove_cvref_t<decltype(t)>;
	return[]<::std::size_t... I>(auto&& t, ::std::index_sequence<I...>) noexcept
	{
		return ::std::make_tuple(get<I>(NGS_PP_PERFECT_FORWARD(t))...);
	}(NGS_PP_PERFECT_FORWARD(t), ::std::make_index_sequence<size_v<tuple_type>>{});
}

NGS_LIB_MODULE_END