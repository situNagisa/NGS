#pragma once

#include "NGS/mpl/defined.h"

NGS_MPL_BEGIN

NGS_MPL_FUNCTION(sequence_param, ccpt::UInt _Index, class _Type) {
	NGS_MPL_TYPE result_type = _Type;
};

template<size_t _Index, class  _Type>
using sequence_params_t = typename sequence_param<ccpt::uint_<_Index>, _Type>::result_type;

NGS_MPL_END
