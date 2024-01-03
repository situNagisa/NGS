#pragma once

#include "./transform.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using identity_matrix = transform_default_sentinel_view <
	[](index_t major, index_t minor) {return major == minor; },
	adapter_extent, adapter_extent > ;

inline constexpr identity_matrix identity = identity_matrix();

NGS_LIB_MODULE_END