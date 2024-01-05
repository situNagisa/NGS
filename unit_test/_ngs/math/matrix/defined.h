#pragma once

#include "NGS/math/matrix.h"
#include <Eigen/Eigen>
#include "../defined.h"

void copy_to_eigen(
	::ngs::math::matrixes::input_matrix auto&& matrix,
	auto& eigen_matrix
)
{
	using namespace ::ngs::math::matrixes;
	for (size_t i = 0; i < ops::major_size(matrix); i++)
	{
		auto&& major = matrix[i];
		for (size_t j = 0; j < ::std::ranges::size(major); j++)
		{
			eigen_matrix(i, j) = major[j];
		}
	}
}

bool is_same_as_eigen(
	::ngs::math::matrixes::input_matrix auto&& matrix,
	auto&& eigen_matrix
)
{
	using namespace ::ngs::math;
	using namespace ::ngs::math::matrixes;

	auto i = ::std::ranges::begin(matrix);
	auto row = eigen_matrix.rowwise();
	auto j = row.begin();
	for (; i != ::std::ranges::end(matrix) && j != row.end(); ++i, ++j)
	{
		if (!vectors::ops::equal(*i, *j))return false;
	}

	return true;
}