#pragma once

#include "./wrapper.h"

NGS_MATH_MATRIX_BEGIN
namespace detail {
template<functor::accessible _Type>
struct matrix_expression_iterator :
	nboost::stl_interfaces::base_random_access_iterator<
	matrix_expression_iterator<_Type>,
	row_vector<_Type>
	>
{
	
};

}

NGS_MATH_MATRIX_END