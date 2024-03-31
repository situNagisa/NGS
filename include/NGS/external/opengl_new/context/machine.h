#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct state_machine {};
template<class T> requires requires { typename type_traits::object_t<T>::machine_type; }
struct state_machine<T>
{
	using type = typename type_traits::object_t<T>::machine_type;
};

template<class T>
using state_machine_t = typename state_machine<T>::type;

template<class Machine>
concept machine = requires(type_traits::naked_t<Machine>&m, typename type_traits::object_t<Machine>::context_type context)
{
	{ type_traits::object_t<Machine>::instance() } -> ::std::convertible_to<type_traits::naked_t<Machine>&>;
	{ m.bind(context) };
};

NGS_LIB_MODULE_END