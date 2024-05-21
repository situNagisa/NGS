#pragma once

#include "./defined.h"

NGS_TYPE_TRAIT_BEGIN

template<ccpt::uint Index, class Type> struct  index_type_identity {
	using result_type = Type;
};

template<size_t _Index, class _Type>
using index_type_identity_t = typename index_type_identity<ccpt::uint_<_Index>, _Type>::result_type;


NGS_TYPE_TRAIT_END
