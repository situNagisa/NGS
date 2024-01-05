#pragma once

#include "./defined.h"

TEST(math_vector, operate)
{
	using namespace ::ngs::math;
	using namespace ::ngs::math::vectors;

	constexpr vector3i static_vector(1, 2, 3);
	vectori dynamic_vector(static_vector);
	constexpr views::trivial_vector adapter_vector(1);

	Eigen::Vector3i e_vector(1, 2, 3);
	Eigen::Vector3i e_a_vector(1, 1, 1);
	{
		static_assert(ops::is_same_size(static_vector, static_vector));
		static_assert(ops::is_same_size(static_vector, adapter_vector));
		EXPECT_TRUE(ops::is_same_size(static_vector, dynamic_vector));
		EXPECT_TRUE(ops::is_same_size(adapter_vector, dynamic_vector));
	}
	{
		EXPECT_TRUE(ops::equal(e_vector, static_vector));
		EXPECT_TRUE(ops::equal(e_vector, dynamic_vector));
		EXPECT_TRUE(ops::equal(e_a_vector, adapter_vector));

		static_assert(static_vector == static_vector);
		static_assert(static_vector != adapter_vector);
		EXPECT_EQ(static_vector, dynamic_vector);
		EXPECT_NE(dynamic_vector, adapter_vector);
	}
	{
		EXPECT_TRUE(ops::equal(-static_vector, -e_vector));
		EXPECT_TRUE(ops::equal(-dynamic_vector, -e_vector));
		EXPECT_TRUE(ops::equal(-adapter_vector, -e_a_vector));
	}
	{
		constexpr vector3i ss_result = -static_vector + static_vector;
		EXPECT_TRUE(ops::equal(ss_result, -e_vector + e_vector));
		vector3i sd_result = -static_vector + dynamic_vector;
		EXPECT_TRUE(ops::equal(sd_result, -e_vector + e_vector));
		vector3i sa_result = -static_vector + adapter_vector;
		EXPECT_TRUE(ops::equal(sa_result, -e_vector + e_a_vector));
		vector3i da_result = dynamic_vector + -adapter_vector;
		EXPECT_TRUE(ops::equal(da_result, e_vector + -e_a_vector));
	}
	{
		//Eigen::Vector3i e_n_vector = e_vector;
		//e_n_vector.normalize();
		//EXPECT_TRUE(ops::equal(views::normalize(static_vector), e_n_vector));
		//EXPECT_TRUE(ops::equal(views::normalize(dynamic_vector), e_n_vector));
	}
	{
		constexpr auto transform = [](index_t index, const vector3i& vector)
			{
				return ops::access(vector, index) + 2;
			};
		constexpr vector3i static_transform = views::transform<transform, 3>(static_vector);
		EXPECT_EQ(static_transform, static_vector + vector3i(2, 2, 2));
		vector3i dynamic_transform = views::transform(dynamic_vector, transform);
		EXPECT_EQ(dynamic_transform, dynamic_vector + vector3i(2, 2, 2));
	}
	{
		EXPECT_TRUE(ops::equal(3 * static_vector, 3 * e_vector));
		EXPECT_TRUE(ops::equal(static_vector * 3, e_vector * 3));
	}
}