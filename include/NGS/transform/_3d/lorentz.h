#pragma once

#include "NGS/transform/defined.h"

NGS_TRANSFORM_BEGIN

template<mla::CVectorDimensionEqual<3> _Velocity,mla::CScalarExpression _Time>
constexpr auto lorentz(const _Velocity& velocity, _Time time = 0.0) {
	auto v = mla::modulus(velocity);
	auto beta = v / numbers::light_speed;
	auto beta_square = beta * beta;
	auto gamma = 1 / std::sqrt(1 - beta_square);

	return gamma * mla::translate(-velocity * time);
}

NGS_TRANSFORM_END
