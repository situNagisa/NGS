#pragma once

#include "NGS/transform/defined.h"
#include "NGS/transform/tag/coordinate.h"

NGS_TRANSFORM_BEGIN

template<CCoordinate _Coordinate, mla::CMatrixLayout _Layout = mla::tag::row>
constexpr auto orthographic(
	const mla::CVectorDimensionEqual<3> auto& src_min,
	const mla::CVectorDimensionEqual<3> auto& src_max,
	const mla::CVectorDimensionEqual<3> auto& dst_min,
	const mla::CVectorDimensionEqual<3> auto& dst_max
) {
	using coordinate_type = _Coordinate;
	using element_type = typename coordinate_type::element_type;
	using vector_type = mla::Vector3<element_type>;
	using matrix_type = mla::HomogeneousMatrix<4, element_type, _Layout>;

	vector_type k = (dst_max - dst_min) / (src_max - src_min);

	constexpr auto index_f = coordinate_type::front_type::index;
	constexpr auto index_r = coordinate_type::right_type::index;
	constexpr auto index_u = coordinate_type::up_type::index;

	constexpr auto sign_f = coordinate_type::front_type::sign;
	constexpr auto sign_r = coordinate_type::right_type::sign;
	constexpr auto sign_u = coordinate_type::up_type::sign;

	std::array<vector_type, 3> xyz{};
	xyz[index_f] = coordinate_type::front_type::value * k[index_f];
	xyz[index_r] = coordinate_type::right_type::value * k[index_r];
	xyz[index_u] = coordinate_type::up_type::value * k[index_u];

	vector_type offset = dst_min - src_min * xyz;

	return matrix_type(
		xyz[0](0), xyz[0](1), xyz[0](2), offset(0),
		xyz[1](0), xyz[1](1), xyz[1](2), offset(1),
		xyz[2](0), xyz[2](1), xyz[2](2), offset(2)
	);
}

NGS_TRANSFORM_END
