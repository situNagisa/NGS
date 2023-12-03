#pragma once

#include "../defined.h"

#if !defined(NGS_CONFIG_LIB_BOOST)
#error boost is not enabled
#endif

#define NGS_BOOST_BEGIN NGS_EXTERNAL_BEGIN namespace nboost{
#define NGS_BOOST_END } NGS_EXTERNAL_END