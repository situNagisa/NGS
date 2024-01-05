#pragma once

#include "./defined.h"

TEST(math_matrix, concept)
{
	using namespace ::ngs::math;
	using namespace ::ngs::math::matrixes;

	using static_type = matrix44f;
	using dynamic_major_type = matrixX3f;
	using dynamic_minor_type = matrix3Xf;
	using adapter_type = views::identity_matrix;

	{
		static_assert(contiguous_matrix<static_type>);
		static_assert(output_matrix<static_type>);

		static_assert(contiguous_matrix<dynamic_major_type>);
		static_assert(output_matrix<dynamic_major_type>);

		static_assert(contiguous_matrix<dynamic_minor_type>);
		static_assert(output_matrix<dynamic_minor_type>);

		static_assert(input_matrix<adapter_type>);
		static_assert(!contiguous_matrix<adapter_type>);
		static_assert(!output_matrix<adapter_type>);
	}
}