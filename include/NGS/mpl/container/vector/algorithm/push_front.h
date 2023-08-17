#pragma once

#include "NGS/mpl/container/vector/vector.h"

NGS_MPL_BEGIN

NGS_mfunction(push_front, CVector _Sequence, class... _NewElements);

NGS_mfunction(push_front, template<class...>class _Sequence, class... _Element, class... _NewElements) < _Sequence<_Element...>, _NewElements... > {
	NGS_mcst_t result_type = _Sequence<_NewElements..., _Element...>;
};

template<CVector _Sequence, class... _NewElement>
using push_front_t = typename push_front<_Sequence, _NewElement...>::result_type;


NGS_MPL_END
