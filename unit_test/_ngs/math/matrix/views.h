#pragma once

#include "./defined.h"

TEST(math_matrix, views)
{
	using namespace ::ngs::math;
	using namespace ::ngs::math::matrixes;

	using static_type = matrix44f;
	using dynamic_major_type = matrixX3f;
	using dynamic_minor_type = matrix3Xf;
	using adapter_type = views::identity_view;

	constexpr static_type static_matrix({ 1,2,3,4 }, { 2,3,4,5 }, { 3,4,5,6 }, { 4,5,6,7 });
	::Eigen::Matrix4f e_matrix{};
	copy_to_eigen(static_matrix, e_matrix);

	{
		constexpr static_type left(static_matrix);
		constexpr static_type right({ 12,23,34,45, }, { 23,34,45,56 }, { 34,45,56,67 }, { 45,56,67,78 });

		::Eigen::Matrix4f e_left{};
		copy_to_eigen(left, e_left);
		::Eigen::Matrix4f e_right{};
		copy_to_eigen(right, e_right);

		ASSERT_TRUE(is_same_as_eigen(left, e_left));
		ASSERT_TRUE(is_same_as_eigen(right, e_right));

		EXPECT_TRUE(is_same_as_eigen(left + right, e_left + e_right));

		EXPECT_TRUE(is_same_as_eigen(left * right, e_left * e_right));
		EXPECT_TRUE(is_same_as_eigen(right * left, e_right * e_left));
		constexpr static_type multi_result = left * right;

		EXPECT_EQ(views::identity, (matrixes::views::transform < [](index_t major, index_t minor) { return major == minor; }, 4, 4 > ()));

		constexpr static_type dynamic_transform = views::transform(left, [](index_t major, index_t minor, auto&& matrix)
			{
				return ops::access(NGS_PP_PERFECT_FORWARD(matrix), major, minor) + 2;
			});
		EXPECT_EQ(dynamic_transform, left + views::trivial(2));

		EXPECT_EQ(left * views::identity, left);
	}
	{
		dynamic_major_type left({ {1,2,3},{2,3,4},{3,4,5},{4,5,6} });
		dynamic_minor_type right({ {1,2,3,4},{2,3,4,5},{3,4,5,6} });
		::Eigen::MatrixXf e_left(4, 3);
		copy_to_eigen(left, e_left);
		::Eigen::MatrixXf e_right(3, 4);
		copy_to_eigen(right, e_right);

		ASSERT_TRUE(is_same_as_eigen(left, e_left));
		ASSERT_TRUE(is_same_as_eigen(right, e_right));

		EXPECT_TRUE(is_same_as_eigen(left * right, e_left * e_right));
		EXPECT_TRUE(is_same_as_eigen(right * left, e_right * e_left));
	}
	{
		EXPECT_TRUE(is_same_as_eigen(views::major_vector(vectors::vector3i(1, 2, 3)), ::Eigen::RowVector3i(1, 2, 3)));
		EXPECT_TRUE(is_same_as_eigen(views::minor_vector(vectors::vector3i(3, 2, 1)), ::Eigen::Vector3i(3, 2, 1)));
		EXPECT_TRUE(is_same_as_eigen(3 * static_matrix, 3 * e_matrix));
		EXPECT_TRUE(is_same_as_eigen(static_matrix * 3, e_matrix * 3));

		::Eigen::Vector4f e_vector = e_matrix * ::Eigen::Vector4f(1, 2, 3, 4);
		EXPECT_TRUE(vectors::ops::equal(static_matrix * vectors::vector4f(1, 2, 3, 4), e_vector));
		e_vector = ::Eigen::RowVector4f(1, 2, 3, 4) * e_matrix;
		EXPECT_TRUE(vectors::ops::equal(vectors::vector4f(1, 2, 3, 4) * static_matrix, e_vector));

		EXPECT_TRUE(vectors::ops::equal(vectors::vector4f(1, 2, 3, 4) * views::identity, vectors::vector4f(1, 2, 3, 4)));
		EXPECT_TRUE(vectors::ops::equal(views::identity * vectors::vector4f(1, 2, 3, 4), vectors::vector4f(1, 2, 3, 4)));
	}
	{
		EXPECT_TRUE(is_same_as_eigen(views::submatrix(static_matrix, { 0,0,3,3 }), e_matrix.block<3, 3>(0, 0)));
	}
}