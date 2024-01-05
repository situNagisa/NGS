#pragma once

#include "NGS/transform/defined.h"

NGS_TRANSFORM_BEGIN

/**
 * \brief			Creates a matrix for a symmetric perspective-view frustum based on the default near and far clip planes definition.
 *
 * \param fov		Specifies the field of view angle in the vertical direction. Expressed in radians.
 * \param aspect	Specifies the aspect ratio that determines the field of view in the horizontal direction. The aspect ratio is the ratio of horizontal (width) to vertical (height).
 * \param near		Specifies the distance from the viewer to the near clipping plane (always positive).
 * \param far		Specifies the distance from the viewer to the far clipping plane (always positive).
 * \param dst_min	Specifies the minimum point of the view space.
 * \param dst_max	Specifies the maximum point of the view space.
 *
 * \tparam _Coordinate	Specifies the screen coordinate system of the view space witch satisfies the `ngs::math::space::CScreenCoordinate` concept.
 * \tparam _ElementType	Specifies the type of the matrix elements.
 * \tparam _Layout		Specifies the layout of the matrix.
 *
 * \return	the perspective projection matrix
*/
template<space::cartesian::d3::CScreen _Coordinate, mla::CScalarExpression _ElementType = float32, mla::CMatrixLayout _Layout = mla::tag::row>
constexpr auto perspective_vertical(
	mla::CScalarExpression auto fov,
	_ElementType aspect,
	_ElementType near,
	_ElementType far,
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
	result(index_d, 3) = sign_d * k;

	result(3, index_d) = 1;

	return result;
}

/**
 * \brief			Creates a matrix for a symmetric perspective-view frustum based on the default near and far clip planes definition.
 *
 * \param fov		Specifies the field of view angle in the horizontal direction. Expressed in radians.
 * \param aspect	Specifies the aspect ratio that determines the field of view in the vertical direction. The aspect ratio is the ratio of vertical (height) to horizontal (width).
 * \param near		Specifies the distance from the viewer to the near clipping plane (always positive).
 * \param far		Specifies the distance from the viewer to the far clipping plane (always positive).
 * \param dst_min	Specifies the minimum point of the view space.
 * \param dst_max	Specifies the maximum point of the view space.
 *
 * \tparam _Coordinate	Specifies the screen coordinate system of the view space witch satisfies the `ngs::math::space::CScreenCoordinate` concept.
 * \tparam _ElementType	Specifies the type of the matrix elements.
 * \tparam _Layout		Specifies the layout of the matrix.
 *
 * \return			the perspective projection matrix
 */
template<space::cartesian::d3::CScreen _Coordinate, mla::CScalarExpression _ElementType = float32, mla::CMatrixLayout _Layout = mla::tag::row>
constexpr auto perspective_horizontal(
	mla::CScalarExpression auto fov,
	_ElementType aspect,
	_ElementType near,
	_ElementType far,
	const mla::CVectorDimensionEqual<3> auto& dst_min,
	const mla::CVectorDimensionEqual<3> auto& dst_max
) {
	using coordinate_type = space::cartesian::d3::screen<typename _Coordinate::vertical_type, typename _Coordinate::horizontal_type, typename _Coordinate::depth_type>;
	return perspective_vertical<coordinate_type, _ElementType, _Layout>(fov, aspect, near, far, dst_min, dst_max);
}

NGS_TRANSFORM_END
