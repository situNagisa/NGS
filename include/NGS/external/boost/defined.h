#pragma once

#include "../defined.h"

#if !defined(NGS_CONFIG_LIB_BOOST)
#error boost is not enabled
#endif

#define NGS_EXTERNAL_BOOST_NS NGS_EXTERNAL_NS::nboost
#define NGS_BOOST_BEGIN namespace NGS_EXTERNAL_BOOST_NS{
#define NGS_BOOST_END }