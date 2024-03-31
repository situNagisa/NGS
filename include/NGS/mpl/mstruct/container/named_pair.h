#pragma once

#include "../variable.h"
#include "../named.h"
#include "./variable.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<statics::strings::string Name, class Variable>
struct named_pair
{
	using name_type = nameds::name_constant<Name>;
	using field_type = meta_variable<Variable>;
};

NGS_LIB_MODULE_END