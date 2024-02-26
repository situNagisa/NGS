#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class, class...>
struct inherit {};

template<class T,class... Bases> requires requires { typename type_traits::object_t<T>::template inherit<Bases...>; }
struct inherit<T,Bases...>
{
	using type = typename type_traits::object_t<T>::template inherit<Bases...>::type;
};

template<class T, class... Bases>
using inherit_t = typename inherit<T, Bases...>::type;

template<class T, class... Bases>
concept inheritable = basic::structure< inherit_t<T, Bases...>>;

NGS_LIB_MODULE_END