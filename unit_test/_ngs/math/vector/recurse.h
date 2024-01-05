#pragma once

#include "./defined.h"

TEST(math_vector, recurse)
{
	using namespace ::ngs::math;
	using namespace ::ngs::math::vectors;

	using recurse_type = vector3<vector<vector2i>>;
	using adapter_type = views::trivial_vector<views::trivial_vector<views::trivial_vector<int>>>;

	static_assert(depth_v< recurse_type> == 3);

	static_assert(contiguous_vector_at<recurse_type, 0>);
	static_assert(contiguous_vector_at<recurse_type, 1>);
	static_assert(contiguous_vector_at<recurse_type, 2>);

	recurse_type recurse_vector({ {1,2} }, { {2,3} }, { {3,4} });
	adapter_type adapter_vector(views::trivial_vector< views::trivial_vector<int>>(views::trivial_vector(2)));

	EXPECT_EQ(recurse::access(recurse_vector, 0, 0, 0), 1);
	EXPECT_EQ(recurse::access(recurse_vector, 0, 0, 1), 2);
	EXPECT_EQ(recurse::access(recurse_vector, 1, 0, 0), 2);
	EXPECT_EQ(recurse::access(recurse_vector, 1, 0, 1), 3);
	EXPECT_EQ(recurse::access(recurse_vector, 2, 0, 0), 3);
	EXPECT_EQ(recurse::access(recurse_vector, 2, 0, 1), 4);

	constexpr auto transformer = [](index_t index, index_t minor, index_t major, auto&& rv)
		{
			return recurse::access(rv, major, minor, index) + 2;
		};
	using transform_view = recurse::transform_depend_view<transformer, const recurse_type&>;
	EXPECT_EQ(recurse::access(transform_view(recurse_vector), 0, 0, 0), recurse::access(recurse_vector, 0, 0, 0) + 2);
	EXPECT_EQ(recurse::access(transform_view(recurse_vector), 0, 0, 1), recurse::access(recurse_vector, 0, 0, 1) + 2);
	EXPECT_EQ(recurse::access(transform_view(recurse_vector), 1, 0, 0), recurse::access(recurse_vector, 1, 0, 0) + 2);
	EXPECT_EQ(recurse::access(transform_view(recurse_vector), 1, 0, 1), recurse::access(recurse_vector, 1, 0, 1) + 2);
	EXPECT_EQ(recurse::access(transform_view(recurse_vector), 2, 0, 0), recurse::access(recurse_vector, 2, 0, 0) + 2);
	EXPECT_EQ(recurse::access(transform_view(recurse_vector), 2, 0, 1), recurse::access(recurse_vector, 2, 0, 1) + 2);
}