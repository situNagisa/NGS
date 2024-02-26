#pragma once

#include "../../variable.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<statics::strings::string Name, variables::variable Variable>
struct named_pair
{
	using name_type = name_constant<Name>;
	using field_type = Variable;
};

NGS_LIB_MODULE_END