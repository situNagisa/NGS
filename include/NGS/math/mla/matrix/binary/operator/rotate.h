#pragma once

#include "NGS/math/mla/matrix/expression/concept.h"
#include "NGS/math/mla/matrix/expression/homogen.h"
#include "NGS/math/mla/scalar/expression/concept.h"
#include "NGS/math/mla/vector/expression/vector.h"
#include "NGS/math/mla/vector/unary/operator/normalize.h"

NGS_MLA_BEGIN

template<CMatrixLayout _Layout = tag::row, CScalarExpression _ScalarExpression>
constexpr auto rotate(_ScalarExpression angle) {
	return HomogeneousMatrix<3, _ScalarExpression, _Layout>(
		std::cos(angle), -std::sin(angle), 0,
		std::sin(angle), std::cos(angle), 0
	);
}

template<CMatrixLayout _Layout = tag::row, CScalarExpression _Pitch, CScalarExpression _Yaw, CScalarExpression _Roll>
constexpr auto rotate(_Pitch pitch, _Yaw yaw, _Roll roll) {
	using element_type = mpl::promote_t<_Pitch, _Yaw, _Roll>;
	HomogeneousMatrix<4, element_type, _Layout> result{};
	
	auto cp = std::cos(static_cast<element_type>(pitch));
	auto sp = std::sin(static_cast<element_type>(pitch));
	auto cy = std::cos(static_cast<element_type>(yaw));
	auto sy = std::sin(static_cast<element_type>(yaw));
	auto cr = std::cos(static_cast<element_type>(roll));
	auto sr = std::sin(static_cast<element_type>(roll));

	result.assign(0, 0, cy * cr);
	result.assign(0, 1, cy * sr);
	result.assign(0, 2, -sy);
	result.assign(1, 0, sp * sy * cr - cp * sr);
	result.assign(1, 1, sp * sy * sr + cp * cr);
	result.assign(1, 2, sp * cy);
	result.assign(2, 0, cp * sy * cr + sp * sr);
	result.assign(2, 1, cp * sy * sr - sp * cr);
	result.assign(2, 2, cp * cy);

	return result;
}

template<class _ElementType = void, CMatrixLayout _Layout = tag::row, CScalarExpression _Angle, CVectorExpression _Axis>
constexpr auto rotate(_Angle angle, const _Axis& axis_temp) {
	using element_type = std::conditional_t<std::same_as<_ElementType, void>,
		mpl::promote_t<_Angle, typename _Axis::element_type>,
		_ElementType>;
	using vector_type = Vector<3, element_type>;
	using matrix_type = HomogeneousMatrix<4, element_type, _Layout>;

	const auto cos = std::cos(static_cast<element_type>(angle));
	const auto sin = std::sin(static_cast<element_type>(angle));

	const vector_type axis = normalize(axis_temp);
	const vector_type temp = (1 - cos) * axis;

	matrix_type result{};

	result.assign(0, 0, cos + temp(0) * axis(0));
	result.assign(0, 1, temp(0) * axis(1) + sin * axis(2));
	result.assign(0, 2, temp(0) * axis(2) - sin * axis(1));

	result.assign(1, 0, temp(1) * axis(0) - sin * axis(2));
	result.assign(1, 1, cos + temp(1) * axis(1));
	result.assign(1, 2, temp(1) * axis(2) + sin * axis(0));

	result.assign(2, 0, temp(2) * axis(0) + sin * axis(1));
	result.assign(2, 1, temp(2) * axis(1) - sin * axis(0));
	result.assign(2, 2, cos + temp(2) * axis(2));

	return result;
}

NGS_MLA_END
