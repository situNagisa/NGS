#pragma once

#include "../variable.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<statics::strings::string Name>
using name_constant = ccpt::auto_constant<Name>;

template<statics::strings::string Name, variables::variable Variable>
using named_field = ::boost::fusion::pair<name_constant<Name>, Variable>;

NGS_LIB_MODULE_END