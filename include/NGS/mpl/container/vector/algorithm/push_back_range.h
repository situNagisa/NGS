#pragma once

#include "NGS/mpl/container/vector/vector.h"

NGS_MPL_BEGIN

NGS_mfunction(push_back_range, CVector _Sequence, CVector _NewSequence);

NGS_mfunction(push_back_range, template<class...>class _Sequence, class... _Element, template<class...>class _NewSequence, class... _NewElements) < _Sequence<_Element...>, _NewSequence<_NewElements...> > {
	NGS_mcst_t result_type = _Sequence<_Element..., _NewElements...>;
};

template<CVector _Sequence, CVector _NewSequence>
using push_back_range_t = typename push_back_range<_Sequence, _NewSequence>::result_type;

NGS_MPL_END
