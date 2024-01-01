#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

namespace detail
{
	void unpack();

	template<class _T, size_t _Index>
	concept unpack_has_adl = requires(_T packet) { unpack<_Index>(NGS_PP_PERFECT_FORWARD(packet)); };

	template<size_t _Index>
	struct unpack_t
	{
		constexpr decltype(auto) operator()(auto&& pack)const requires unpack_has_adl<decltype(pack), _Index>
		{
			if constexpr (unpack_has_adl<decltype(pack), _Index>)
			{
				return unpack<_Index>(NGS_PP_PERFECT_FORWARD(pack));
			}
		}
	};
}

template<size_t _Index>
inline constexpr detail::unpack_t<_Index> unpack{};

NGS_LIB_END
