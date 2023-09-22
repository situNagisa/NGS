#pragma once

#include "NGS/transform/defined.h"

NGS_TRANSFORM_BEGIN

template<
	space::CDirectionCoordinate _Coordinate,
	mla::CScalarExpression _ElementType = float32,
	mla::CMatrixLayout _Layout = mla::tag::row,
	mla::CVectorDimensionEqual<3> _Direction,
	mla::CScalarExpression _Theta>
constexpr auto direction(const _Direction& direction, _Theta theta) {
	using coordinate_type = _Coordinate;
	using element_type = _ElementType;
	using vector_type = mla::Vector3<element_type>;
	using matrix_type = mla::HomogeneousMatrix<4, element_type, _Layout>;

	constexpr auto index_f = coordinate_type::front_type::dimension;
	constexpr auto index_r = coordinate_type::right_type::dimension;
	constexpr auto index_u = coordinate_type::up_type::dimension;

	constexpr auto sign_f = coordinate_type::front_type::sign;
	constexpr auto sign_r = coordinate_type::right_type::sign;
	constexpr auto sign_u = coordinate_type::up_type::sign;

	std::array<vector_type, 3> xyz{};

	xyz[index_f] = mla::normalize(direction);
	xyz[index_r] = mla::product_outer(xyz[index_f], base_vector<typename coordinate_type::up_type,3,element_type>());
	xyz[index_u] = mla::product_outer(xyz[index_r], xyz[index_f]);

	auto& x = xyz[0];
	auto& y = xyz[1];
	auto& z = xyz[2];

	matrix_type result = mla::rotate<element_type, _Layout>(theta, base_vector<typename coordinate_type::front_type, 3, element_type>())* matrix_type(
		x(0), x(1), x(2), 0,
		y(0), y(1), y(2), 0,
		z(0), z(1), z(2), 0
	);
	return result;
}

NGS_TRANSFORM_END
