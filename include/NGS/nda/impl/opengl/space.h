#pragma once

#include "NGS/nda/impl/opengl/defined.h"

NDA_IMPL_OPENGL_BEGIN

inline constexpr auto opengl_space = mla::static_matrix_v<3, 3, number_t,
	2.0f, 0.0f, 0.0f,
	0.0f, -2.0f, 0.0f,
	0.0f, 0.0f, 1.0f>;

NDA_IMPL_OPENGL_END
