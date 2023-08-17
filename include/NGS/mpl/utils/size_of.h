#pragma once

#include "NGS/mpl/defined.h"

NGS_MPL_BEGIN

NGS_mfunction(size_of, class _Type) {
	NGS_mcst_t result_type = ccpt::uint_<sizeof(_Type)>;
};

template<class _Type>
using size_of_t = typename size_of<_Type>::result_type;

template<class _Type>
constexpr size_t size_of_v = size_of_t<_Type>::value;

NGS_MPL_END
