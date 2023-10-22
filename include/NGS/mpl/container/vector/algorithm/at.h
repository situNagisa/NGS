#pragma once

#include "NGS/mpl/container/vector/vector.h"

NGS_MPL_BEGIN

NGS_MPL_FUNCTION(at, CVector _Sequence, ccpt::uint _Index) {
	NGS_MPL_TYPE result_type = typename _Sequence::template at<_Index>;
};

template<CVector _Sequence, size_t _Index>
using at_c = at<_Sequence, ccpt::uint_<_Index>>;

template<CVector _Sequence, ccpt::uint _Index>
using at_t = typename at<_Sequence, _Index>::result_type;



NGS_MPL_END
