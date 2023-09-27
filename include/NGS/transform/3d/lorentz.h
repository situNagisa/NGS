#pragma once

#include "NGS/transform/defined.h"

NGS_TRANSFORM_BEGIN

/**
 * \brief Lorentz transformation
 * 
 * \param relative_velocity 
 * \param delta_time
 * \param light_speed
 * \return 
 */
template<mla::CVectorDimensionEqual<3> _Velocity>
constexpr auto lorentz(const _Velocity& relative_velocity, mla::CScalarExpression auto delta_time = 0.0, mla::CScalarExpression auto light_speed = numbers::light_speed) {
	using element_type = typename _Velocity::element_type;
	using vector_type = mla::Vector3<element_type>;
	using matrix_type = mla::Matrix<4, 4,element_type>;

	auto v = mla::modulus(relative_velocity);
	vector_type e = v ? relative_velocity / v : vector_type{};
	auto beta = v / light_speed;
	auto beta_square = beta * beta;
	auto gamma = 1 / std::sqrt(1 - beta_square);
	auto gamma_1 = gamma - 1;

	matrix_type result = mla::identity_matrix_v<4, element_type>;

	result.assign(0, 0, gamma_1 * e(0) * e(0) + 1);
	result.assign(0, 1, gamma_1 * e(0) * e(1));
	result.assign(0, 2, gamma_1 * e(0) * e(2));
	result.assign(0, 3, - gamma * e(0) * v * delta_time);

	result.assign(1, 0, gamma_1 * e(1) * e(0));
	result.assign(1, 1, gamma_1 * e(1) * e(1) + 1);
	result.assign(1, 2, gamma_1 * e(1) * e(2));
	result.assign(1, 3, - gamma * e(1) * v * delta_time);

	result.assign(2, 0, gamma_1 * e(2) * e(0));
	result.assign(2, 1, gamma_1 * e(2) * e(1));
	result.assign(2, 2, gamma_1 * e(2) * e(2) + 1);
	result.assign(2, 3, - gamma * e(2) * v * delta_time);

	return result;
}

NGS_TRANSFORM_END
