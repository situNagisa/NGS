#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct viewport
{
	using viewport_type = math::boxes::containers::hypercube<3, float, float>;
	using scissor_type = math::boxes::containers::hypercube<2, int32_t, uint32_t>;

	::std::span<viewport_type> viewports{};
	::std::span<scissor_type> scissors{};
};

NGS_LIB_MODULE_END