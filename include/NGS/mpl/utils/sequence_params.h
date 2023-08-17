#pragma once

#include "NGS/mpl/defined.h"

NGS_MPL_BEGIN

NGS_mfunction(sequence_param, ccpt::UInt _Index, class _Type) {
	NGS_mcst_t result_type = _Type;
};

template<size_t _Index, class  _Type>
using sequence_params_t = typename sequence_param<ccpt::uint_<_Index>, _Type>::result_type;

NGS_MPL_END
