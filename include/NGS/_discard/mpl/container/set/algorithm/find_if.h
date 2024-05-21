#pragma once

#include "NGS/mpl/container/set/set.h"
#include "NGS/mpl/functor/find_if.h"
#include "NGS/mpl/container/vector/vector.h"
#include "NGS/mpl/container/vector/algorithm/find.h"

NGS_MPL_BEGIN

NGS_MPL_FUNCTION(find_if, CSet _Rng, template<class...>class _Predicate) < _Rng, _Predicate > {
public:
	using result_type = find_if_t<typename _Rng::container, _Predicate>;
};

NGS_MPL_END
