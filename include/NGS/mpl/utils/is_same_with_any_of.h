#pragma once

#include "NGS/mpl/container/vector/vector.h"
#include "NGS/mpl/container/vector/algorithm/find.h"

NGS_MPL_BEGIN

NGS_mfunction(is_same_with_any_of, class _With, CVector _Rng) {
	template<class _T>
	struct predicate_type {
		using result_type = std::is_same<_T, _With>;
	};
	using result_type = ccpt::bool_<find_if_v<_Rng, predicate_type> != -1>;
};
template<class _With, class... _Elements>
using is_same_with_any_of_t = typename is_same_with_any_of<_With, vector<_Elements...>>::result_type;
template<class _With, class... _Elements>
constexpr bool is_same_with_any_of_v = is_same_with_any_of_t<_With, _Elements...>::value;

NGS_MPL_END
