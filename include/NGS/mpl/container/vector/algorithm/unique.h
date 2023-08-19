#pragma once

#include "NGS/mpl/container/vector/vector.h"
#include "NGS/mpl/container/vector/algorithm/filter.h"
#include "NGS/mpl/container/vector/algorithm/view.h"
#include "NGS/mpl/utils/is_same_with_any_of.h"
#include "NGS/mpl/functor/equal.h"

NGS_MPL_BEGIN

NGS_mfunction(unique, CVector _Sequence,template<class,class>class _Predicate = identically_equal) {
	template<class _S, class _I>
	struct predicate_type {
		using result_type = ccpt::bool_<!is_same_with_any_of<view_t<_S, _I>, typename _S::template at<_I>, _Predicate>::result_type::value>;
	};

	NGS_mcst_t result_type = filter_t<_Sequence, predicate_type>;
};
template<CVector _Sequence, template<class, class>class _Predicate = identically_equal>
using unique_t = typename unique<_Sequence, _Predicate>::result_type;

NGS_MPL_END
