#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

BOOST_AUTO_TEST_CASE(container_vector)
{
	static_assert(contiguous_vector<vector<int, 3>>, "vector is not satisfy contiguous_vector");
	static_assert(contiguous_vector<vector<int>>, "vector is not satisfy contiguous_vector");

	vector<int, 3> b(1, 2, 3);
}

NGS_LIB_END