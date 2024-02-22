#pragma once

#include "./defined.h"

NGS_TYPE_TRAIT_BEGIN

NGS_MPL_FUNCTION(index_type_identity, ccpt::uint _Index, class _Type) {
	NGS_MPL_TYPE result_type = _Type;
};

template<size_t _Index, class _Type>
using index_type_identity_t = typename index_type_identity<ccpt::uint_<_Index>, _Type>::result_type;


NGS_TYPE_TRAIT_END
