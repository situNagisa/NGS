#pragma once

#include "NGS/transform/defined.h"
#include "NGS/transform/tag/coordinate.h"

NGS_TRANSFORM_BEGIN

template<CCoordinate _Coordinate, mla::CMatrixLayout _Layout = mla::tag::row>
constexpr auto perspective(
	mla::CScalarExpression auto fov,
	mla::CScalarExpression auto aspect,
	mla::CScalarExpression auto near,
	mla::CScalarExpression auto far,
	const mla::CVectorDimensionEqual<3> auto& dst_min,
	const mla::CVectorDimensionEqual<3> auto& dst_max
) {
	using coordinate_type = _Coordinate;
	using element_type = typename coordinate_type::element_type;
	using matrix_type = mla::Matrix<4, 4, element_type, _Layout>;

	matrix_type result{};

	auto tan = std::tan(fov / 2);

	constexpr auto index_f = coordinate_type::front_type::index;
	constexpr auto index_r = coordinate_type::right_type::index;
	constexpr auto index_u = coordinate_type::up_type::index;

	constexpr auto sign_f = coordinate_type::front_type::sign;
	constexpr auto sign_r = coordinate_type::right_type::sign;
	constexpr auto sign_u = coordinate_type::up_type::sign;

	mla::Vector3<element_type> sum = dst_max + dst_min;
	mla::Vector3<element_type> difference = dst_max - dst_min;


	result(index_r, index_r) = sign_r * difference(index_r) / (2 * aspect * tan);
	result(index_r, index_f) = sign_r * sum(index_r) / 2;

	result(index_u, index_u) = sign_u * difference(index_u) / (2 * tan);
	result(index_u, index_f) = sign_u * sum(index_u) / 2;

	auto k = difference(index_f) * far / (far - near);
	auto b = -near * k;

	result(index_f, index_f) = sign_f * k;
	result(index_f, 3)		 = sign_f * b;

	result(3,index_f) = 1;

	return result;
}

NGS_TRANSFORM_END
