#pragma once

#include "./concept.h"

NGS_NGL_FUSION_BEGIN

template<cpt::fundamental _Type, size_t _Count = 1>
using attrib = mpl::mstruct::variable<_Type[_Count]>;

NGS_NGL_FUSION_END
