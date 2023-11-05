#pragma once

#include "NGS/basic/basic.h"

#define NGS_BOOST_BEGIN NGS_BEGIN namespace nboost{
#define NGS_BOOST_END } NGS_END

#if !defined(NGS_CONFIG_LIB_BOOST)
#error boost is not enabled
#endif
