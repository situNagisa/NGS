#pragma once

#include "./machine.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace detail
{
	template<class _State>
	concept has_member = requires(_State s)
	{
		{ NGS_PP_PERFECT_FORWARD(s).bind() };
	};

	template<class _State>
	concept has_adl = requires(_State s)
	{
		{ bind(NGS_PP_PERFECT_FORWARD(s)) };
	};
}

template<class T>
concept bindable = detail::has_member<T> || detail::has_adl<T> || machine<state_machine_t<T>>;

inline constexpr struct
{
	constexpr decltype(auto) operator()(bindable auto&& s)const
	{
		using state_type = decltype(s);

		if constexpr (detail::has_member<state_type>)
		{
			return NGS_PP_PERFECT_FORWARD(s).bind();
		}
		else if constexpr (detail::has_adl<state_type>)
		{
			return bind(NGS_PP_PERFECT_FORWARD(s));
		}
		else if constexpr (machine<state_machine_t<state_type>>)
		{
			typename state_machine_t<state_type>::instance().bind(NGS_PP_PERFECT_FORWARD(s));
		}
		else
		{
			static_assert(cpt::none<decltype(s)>, "bind not found");
		}
	}
}bind{};

NGS_LIB_MODULE_END