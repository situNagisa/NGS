#pragma once

#include "NGS/mpl/defined.h"

NGS_MPL_BEGIN

NGS_mfunction(precision, class _Type) { NGS_mcst_t result_type = _Type; };

NGS_mfunction(precision) < float > { NGS_mcst_t result_type = double; };
NGS_mfunction(precision) < double > { NGS_mcst_t result_type = long double; };

NGS_mfunction(precision) < int8 > { NGS_mcst_t result_type = int16; };
NGS_mfunction(precision) < int16 > { NGS_mcst_t result_type = int32; };
NGS_mfunction(precision) < int32 > { NGS_mcst_t result_type = int64; };

NGS_mfunction(precision) < uint8 > { NGS_mcst_t result_type = uint16; };
NGS_mfunction(precision) < uint16 > { NGS_mcst_t result_type = uint32; };
NGS_mfunction(precision) < uint32 > { NGS_mcst_t result_type = uint64; };

template<class _Type>
using precision_t = typename precision<_Type>::result_type;

NGS_MPL_END
