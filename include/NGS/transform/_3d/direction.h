#pragma once

#include "NGS/transform/defined.h"
#include "NGS/transform/tag/coordinate.h"

NGS_TRANSFORM_BEGIN

template<
	CCoordinate _Coordinate,
	mla::CMatrixLayout _Layout = mla::tag::row,
	mla::CVectorDimensionEqual<3> _Direction,
	mla::CScalarExpression _Theta>
constexpr auto direction(const _Direction& direction, _Theta theta) {
	using coordinate_type = _Coordinate;
	using element_type = typename coordinate_type::element_type;
	using vector_type = mla::Vector3<element_type>;
	using matrix_type = mla::HomogeneousMatrix<4, element_type, _Layout>;

	vector_type front = mla::normalize(direction);
	vector_type right = mla::product_outer(front, coordinate_type::up_type::value);
	vector_type up = mla::product_outer(right, front);
	std::array<vector_type*, 3> xyz{};

	xyz[coordinate_type::front_type::index] = &front;
	xyz[coordinate_type::right_type::index] = &right;
	xyz[coordinate_type::up_type::index] = &up;

	auto& x = *xyz[0];
	auto& y = *xyz[1];
	auto& z = *xyz[2];

	matrix_type result = mla::rotate<element_type, _Layout>(theta, coordinate_type::front_type::value)* matrix_type(
		x(0), x(1), x(2), 0,
		y(0), y(1), y(2), 0,
		z(0), z(1), z(2), 0
	);
	return result;
}

NGS_TRANSFORM_END
