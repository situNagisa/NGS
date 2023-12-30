#pragma once

#include "./transform.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using identity_matrix = transform_view < adapter_extent, adapter_extent,
	[](index_t major, index_t minor) {return major == minor; },
	default_major_sizer<adapter_extent>(), default_minor_sizer<adapter_extent>() > ;

inline constexpr identity_matrix identity = identity_matrix();

NGS_LIB_MODULE_END