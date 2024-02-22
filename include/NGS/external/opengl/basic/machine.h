#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct state_machine {};
template<class _T> requires requires { typename type_traits::object_t<_T>::machine_type; }
struct state_machine<_T>
{
	using type = typename type_traits::object_t<_T>::machine_type;
};

template<class _T>
using state_machine_t = typename state_machine<_T>::type;

template<class _Machine>
concept machine = requires(type_traits::naked_t<_Machine>&m, typename type_traits::object_t<_Machine>::context_type context)
{
	{ type_traits::object_t<_Machine>::instance() } -> std::convertible_to<type_traits::naked_t<_Machine>&>;
	{ m.bind(context) };
};

NGS_LIB_MODULE_END