#pragma once

#include "NGS/nda/depend.h"

#ifndef NDA_NUMBER_TYPE
#define NDA_NUMBER_TYPE ngs::float32
#endif
static_assert(ngs::Arithmetic<NDA_NUMBER_TYPE>, "NDA_NUMBER_TYPE must is number type");

#ifndef NDA_COLOR_TYPE
#define NDA_COLOR_TYPE ngs::ARGB32
#endif
