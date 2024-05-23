#pragma once

#include "../concept.h"
#include "./atomic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class T, class Result>
	concept to_integral_has_member = requires(T t)
	{
		{ NGS_PP_PERFECT_FORWARD(t).template to_integral<Result>() } -> ::std::convertible_to<Result>;
	};

	template<class T, class Result>
	concept to_integral_has_adl = requires(T t)
	{
		{ to_integral<Result>(NGS_PP_PERFECT_FORWARD(t)) } -> ::std::convertible_to<Result>;
	};

	template<class Result = ::std::uintmax_t>
	struct to_integral_functor
	{
		NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(const concepts::range auto& range) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST noexcept
		{
			if constexpr (to_integral_has_member<decltype(range), Result>)
			{
				return static_cast<Result>(range.template to_integral<Result>());
			}
			else if constexpr (to_integral_has_adl<decltype(range), Result>)
			{
				return static_cast<Result>(to_integral<Result>(range));
			}
			else
			{
				auto result = static_cast<Result>(0);
				for (const auto&[index, value] : range | ::std::views::enumerate)
				{
					static_cast<bool>(value) ? NGS_LIB_MODULE_NAME::set(result, index) : NGS_LIB_MODULE_NAME::reset(result, index);
				}
				return result;
			}
		}
	};
}

template<concepts::fundamental Result = ::std::uintmax_t>
inline constexpr _detail::to_integral_functor<Result> to_integral{};

NGS_LIB_MODULE_END