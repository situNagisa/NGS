#pragma once

#include "../operate.h"
#include "./transform.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using identity_view = NGS_MATH_MATRIX_TAG_NS::retag < NGS_MATH_MATRIX_TAG_NS::identity, transform_default_sentinel_view <
	[](index_t major, index_t minor) {return major == minor; },
	adapter_extent, adapter_extent > > ;

inline constexpr identity_view identity{};

NGS_LIB_MODULE_END