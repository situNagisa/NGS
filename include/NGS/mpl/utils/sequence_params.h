#pragma once

#include "NGS/mpl/defined.h"

NGS_MPL_BEGIN

NGS_MPL_FUNCTION(index_type_identity, ccpt::UInt _Index, class _Type) {
	NGS_MPL_TYPE result_type = _Type;
};

template<size_t _Index, class  _Type>
using sequence_params_t = typename index_type_identity<ccpt::uint_<_Index>, _Type>::result_type;

NGS_MPL_END
