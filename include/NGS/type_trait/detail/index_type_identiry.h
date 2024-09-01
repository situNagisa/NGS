#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<::std::size_t, class Type>
struct  index_type_identity
{
	using type = Type;
};

template<::std::size_t Index, class Type>
using index_type_identity_t = typename index_type_identity<Index, Type>::type;


NGS_LIB_MODULE_END
