#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct variable_value{};
template<class Variable>
using variable_value_t = typename variable_value<Variable>::type;

template<class Variable> requires requires{ typename type_traits::object_t<Variable>::value_type; }
struct variable_value<Variable>
{
	using type = typename type_traits::object_t<Variable>::value_type;
};

NGS_LIB_MODULE_END