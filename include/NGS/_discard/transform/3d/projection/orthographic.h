#pragma once

#include "NGS/transform/defined.h"

NGS_TRANSFORM_BEGIN

template<space::cartesian::d3::CScreen _Coordinate, mla::CScalarExpression _ElementType = float32, mla::CMatrixLayout _Layout = mla::tag::row>
constexpr auto orthographic(
	const mla::CVectorDimensionEqual<3> auto& src_min,
	const mla::CVectorDimensionEqual<3> auto& src_max,
	const mla::CVectorDimensionEqual<3> auto& dst_min,
	const mla::CVectorDimensionEqual<3> auto& dst_max
) {
	using coordinate_type = _Coordinate;
	using element_type = _ElementType;
	using vector_type = mla::Vector3<element_type>;
	using matrix_type = mla::HomogeneousMatrix<4, element_type, _Layout>;

	vector_type k = (dst_max - dst_min) / (src_max - src_min);

	constexpr auto index_h = coordinate_type::horizontal_type::dimension;
	constexpr auto index_v = coordinate_type::vertical_type::dimension;
	constexpr auto index_d = coordinate_type::depth_type::dimension;

	constexpr auto sign_h = coordinate_type::horizontal_type::sign;
	constexpr auto sign_v = coordinate_type::vertical_type::sign;
	constexpr auto sign_d = coordinate_type::depth_type::sign;

	std::array<vector_type, 3> xyz{};
	xyz[index_h](index_h) = sign_h * k[index_h];
	xyz[index_v](index_v) = sign_v * k[index_v];
	xyz[index_d](index_d) = sign_d * k[index_d];

	vector_type offset = dst_min - src_min * vector_type(xyz[0][0], xyz[1][1], xyz[2][2]);

	return matrix_type(
		xyz[0](0), xyz[0](1), xyz[0](2), offset(0),
		xyz[1](0), xyz[1](1), xyz[1](2), offset(1),
		xyz[2](0), xyz[2](1), xyz[2](2), offset(2)
	);
}

NGS_TRANSFORM_END
