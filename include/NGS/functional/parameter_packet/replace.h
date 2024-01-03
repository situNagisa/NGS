#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

namespace detail
{
	void replace();

	template<class _T, class... _Args>
	concept replace_has_adl = requires(_T param, _Args... replace_params) { replace(NGS_PP_PERFECT_FORWARD(param), NGS_PP_PERFECT_FORWARD(replace_params)...); };

	struct replace_t
	{
		constexpr decltype(auto) operator()(auto&& param, auto&&... replace_params)const
		{
			if constexpr (replace_has_adl<decltype(param), decltype(replace_params)...>)
			{
				return replace(NGS_PP_PERFECT_FORWARD(param), NGS_PP_PERFECT_FORWARD(replace_params)...);
			}
			else
			{
				return NGS_PP_PERFECT_FORWARD(param);
			}
		}
	};
}

inline constexpr detail::replace_t replace{};

template<class _First, class...>
struct meta_replace
{
	using type = _First;
};
template<class _First, class... _Args> using meta_replace_t = typename meta_replace<_First, _Args...>::type;

NGS_LIB_END