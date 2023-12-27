#pragma once

#include "../vector.h"

#define BOOST_TEST_MODULE ::ngs::math::vector test
#include <boost/test/unit_test.hpp>

#define NGS_MATH_VECTOR_TEST_NS NGS_MATH_VECTOR_NS::test
#define NGS_LIB_NAME NGS_MATH_VECTOR_TEST_NS
#include "NGS/lib/lib.h"