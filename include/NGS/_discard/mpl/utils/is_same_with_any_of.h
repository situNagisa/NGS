#pragma once

#include "NGS/mpl/container/vector/vector.h"
#include "NGS/mpl/container/vector/algorithm/find.h"
#include "NGS/mpl/functor/equal.h"

NGS_MPL_BEGIN

NGS_MPL_FUNCTION(is_same_with_any_of, CVector _Rng, class _With,template<class,class>class _Functor = identically_equal) {
	template<class _T>
	struct predicate_type {
		using result_type = typename _Functor<_T, _With>::result_type;
	};
	using result_type = ccpt::bool_<find_if_t<_Rng, predicate_type>::value != -1>;
};
template<class _With, class... _Elements>
using is_same_with_any_of_t = typename is_same_with_any_of<vector<_Elements...>, _With>::result_type;
template<class _With, class... _Elements>
constexpr bool is_same_with_any_of_v = is_same_with_any_of_t<_With, _Elements...>::value;

NGS_MPL_END
