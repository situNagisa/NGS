#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<statics::strings::string Name>
using name_constant = ccpt::auto_constant<Name>;

template<class T>
concept name = statics::strings::static_string<typename type_traits::object_t<T>::type> && statics::strings::static_string<decltype(type_traits::object_t<T>::type::value)>;


template<class> struct named_pair_name {};
template<class Field>
using named_pair_name_t = typename named_pair_name<Field>::type;

template<class Field> requires requires{ typename type_traits::object_t<Field>::name_type; }
struct named_pair_name<Field>
{
	using type = typename type_traits::object_t<Field>::name_type;
};


NGS_LIB_MODULE_END