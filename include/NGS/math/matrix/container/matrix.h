#pragma once

#include "../extent.h"
#include "../tag.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _E, extent_t _Major = dynamic_extent, extent_t _Minor = dynamic_extent>
struct matrix : basic_matrix, vectors::vector<vectors::vector<_E, _Minor>, _Major>
{
	using base_type = vectors::vector<vectors::vector<_E, _Minor>, _Major>;
	using basic_matrix::nmla_type;

	using base_type::base_type;
	using base_type::operator=;
};

#define NGS_MATH_MATRIX_CONSTANT(major_id,major_extent,minor_id,minor_extent)					\
template<class _E> using matrix##major_id##minor_id = matrix<_E, major_extent, minor_extent>;	\
using matrix##major_id##minor_id##i = matrix##major_id##minor_id<int>;							\
using matrix##major_id##minor_id##f = matrix##major_id##minor_id<float>;						\
using matrix##major_id##minor_id##d = matrix##major_id##minor_id<double>;						\
using matrix##major_id##minor_id##s = matrix##major_id##minor_id<size_t>;						\
using matrix##major_id##minor_id##ci = matrix##major_id##minor_id<::std::complex<int>>;			\
using matrix##major_id##minor_id##cf = matrix##major_id##minor_id<::std::complex<float>>;		\
using matrix##major_id##minor_id##cd = matrix##major_id##minor_id<::std::complex<double>>;		\
using matrix##major_id##minor_id##cs = matrix##major_id##minor_id<::std::complex<size_t>>		\
//
#define NGS_MATH_MATRIX_CONSTANT_X_X(major_extent,minor_extent) NGS_MATH_MATRIX_CONSTANT(major_extent,major_extent,minor_extent,minor_extent)
#define NGS_MATH_MATRIX_CONSTANT_X_D(major_extent,minor_extent) NGS_MATH_MATRIX_CONSTANT(major_extent,major_extent,X, dynamic_extent)
#define NGS_MATH_MATRIX_CONSTANT_D_X(major_extent,minor_extent) NGS_MATH_MATRIX_CONSTANT(X, dynamic_extent,minor_extent,minor_extent)
#define NGS_MATH_MATRIX_CONSTANT_D_D(major_extent,minor_extent) NGS_MATH_MATRIX_CONSTANT(X, dynamic_extent,X, dynamic_extent)

#define NGS_MATH_MATRIX_GENERATE_CONSTANT(generate_functor)	\
generate_functor(1, 1);										\
generate_functor(1, 2);										\
generate_functor(1, 3);										\
generate_functor(1, 4);										\
generate_functor(2, 1);										\
generate_functor(2, 2);										\
generate_functor(2, 3);										\
generate_functor(2, 4);										\
generate_functor(3, 1);										\
generate_functor(3, 2);										\
generate_functor(3, 3);										\
generate_functor(3, 4);										\
generate_functor(4, 1);										\
generate_functor(4, 2);										\
generate_functor(4, 3);										\
generate_functor(4, 4);										\
//

NGS_MATH_MATRIX_GENERATE_CONSTANT(NGS_MATH_MATRIX_CONSTANT_X_X);
NGS_MATH_MATRIX_GENERATE_CONSTANT(NGS_MATH_MATRIX_CONSTANT_X_D);
NGS_MATH_MATRIX_GENERATE_CONSTANT(NGS_MATH_MATRIX_CONSTANT_D_X);
NGS_MATH_MATRIX_GENERATE_CONSTANT(NGS_MATH_MATRIX_CONSTANT_D_D);

NGS_LIB_MODULE_END