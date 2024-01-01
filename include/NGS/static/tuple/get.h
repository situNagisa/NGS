#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

namespace detail
{
	//for ADL
	void get();

	template<class _T, size_t _Index>
	concept get_has_member = requires(_T tuple) { NGS_PP_PERFECT_FORWARD(tuple).template get<_Index>(); };

	template<class _T, size_t _Index>
	concept get_has_adl = requires(_T tuple) { get<_Index>(NGS_PP_PERFECT_FORWARD(tuple)); };

	template<size_t _Index>
	struct get_t
	{
		constexpr decltype(auto) operator()(auto&& tuple)const requires get_has_member<decltype(tuple), _Index> || get_has_adl<decltype(tuple), _Index>
		{
			if constexpr (get_has_member<decltype(tuple), _Index>)
			{
				return NGS_PP_PERFECT_FORWARD(tuple).template get<_Index>();
			}
			else if constexpr (get_has_adl<decltype(tuple), _Index>)
			{
				return get<_Index>(NGS_PP_PERFECT_FORWARD(tuple));
			}
			else
			{
				static_assert(
					cpt::none<decltype(tuple)>,
					"tuple does not have get method"
					);
			}
		}
	};
}

template<size_t _Index>
inline constexpr detail::get_t<_Index> get{};

NGS_LIB_END