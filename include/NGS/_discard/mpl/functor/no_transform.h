#pragma once

#include "NGS/mpl/defined.h"

NGS_MPL_BEGIN

NGS_MPL_FUNCTION(no_transform, class _Type) {
	NGS_MPL_TYPE result_type = _Type;
};
template<class _Type> using no_transform_t = typename no_transform<_Type>::result_type;

NGS_MPL_END
