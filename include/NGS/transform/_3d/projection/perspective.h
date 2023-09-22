#pragma once

#include "NGS/transform/defined.h"

NGS_TRANSFORM_BEGIN

template<space::CScreenCoordinate _Coordinate, mla::CScalarExpression _ElementType = float32, mla::CMatrixLayout _Layout = mla::tag::row>
constexpr auto perspective(
	mla::CScalarExpression auto fov,
	mla::CScalarExpression auto aspect,
	mla::CScalarExpression auto near,
	mla::CScalarExpression auto far,
	const mla::CVectorDimensionEqual<3> auto& dst_min,
	const mla::CVectorDimensionEqual<3> auto& dst_max
) {
	using coordinate_type = _Coordinate;
	using element_type = _ElementType;
	using matrix_type = mla::Matrix<4, 4, element_type, _Layout>;

	matrix_type result{};

	auto tan = std::tan(fov / 2);

	constexpr auto index_h = coordinate_type::horizontal_type::dimension;
	constexpr auto index_v = coordinate_type::vertical_type::dimension;
	constexpr auto index_d = coordinate_type::depth_type::dimension;

	constexpr auto sign_h = coordinate_type::horizontal_type::sign;
	constexpr auto sign_v = coordinate_type::vertical_type::sign;
	constexpr auto sign_d = coordinate_type::depth_type::sign;

	mla::Vector3<element_type> sum = dst_max + dst_min;
	mla::Vector3<element_type> difference = dst_max - dst_min;


	result(index_h, index_h) = sign_v * difference(index_h) / (2 * aspect * tan);
	result(index_h, index_d) = sign_v * sum(index_h) / 2;

	result(index_v, index_v) = sign_h * difference(index_v) / (2 * tan);
	result(index_v, index_d) = sign_h * sum(index_v) / 2;

	auto k = difference(index_d) * far * near / (near - far);
	auto b = dst_min(index_d) - k / near;

	result(index_d, index_d) = sign_d * b;
	result(index_d, 3)		 = sign_d * k;

	result(3,index_d) = 1;

	return result;
}

NGS_TRANSFORM_END
