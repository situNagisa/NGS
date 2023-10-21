#pragma once

#include "./defined.h"

NGS_TYPE_TRAIT_BEGIN

NGS_MPL_FUNCTION(precision, class _Type) { NGS_MPL_TYPE result_type = _Type; };

NGS_MPL_FUNCTION(precision) < float > { NGS_MPL_TYPE result_type = double; };
NGS_MPL_FUNCTION(precision) < double > { NGS_MPL_TYPE result_type = long double; };

NGS_MPL_FUNCTION(precision) < int8 > { NGS_MPL_TYPE result_type = int16; };
NGS_MPL_FUNCTION(precision) < int16 > { NGS_MPL_TYPE result_type = int32; };
NGS_MPL_FUNCTION(precision) < int32 > { NGS_MPL_TYPE result_type = int64; };

NGS_MPL_FUNCTION(precision) < uint8 > { NGS_MPL_TYPE result_type = uint16; };
NGS_MPL_FUNCTION(precision) < uint16 > { NGS_MPL_TYPE result_type = uint32; };
NGS_MPL_FUNCTION(precision) < uint32 > { NGS_MPL_TYPE result_type = uint64; };

template<class _Type>
using precision_t = typename precision<_Type>::result_type;

NGS_TYPE_TRAIT_END
