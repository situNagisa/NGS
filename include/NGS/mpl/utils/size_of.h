#pragma once

#include "NGS/mpl/defined.h"

NGS_MPL_BEGIN

NGS_MPL_FUNCTION(size_of, class _Type,ccpt::uint _Align = ccpt::uint_<0>) {
	NGS_MPL_TYPE result_type = decltype([] {
		if constexpr (!_Align::value || !std::is_fundamental_v<_Type>) {
			return declval<ccpt::uint_<sizeof(_Type)>>();
		}
		else {
			if constexpr (sizeof(_Type) % _Align::value) {
				return declval<ccpt::uint_<sizeof(_Type) + _Align::value - sizeof(_Type) % _Align::value>>();
			}
			else {
				return declval<ccpt::uint_<sizeof(_Type)>>();
			}
		}
		}());
};

template<class _Type>
using size_of_t = typename size_of<_Type>::result_type;

template<class _Type>
constexpr size_t size_of_v = size_of_t<_Type>::value;

NGS_MPL_END
