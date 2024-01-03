#pragma once

#include "./transform.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _T>
using trivial_matrix = transform_default_sentinel_view <
	[](index_t, index_t, auto&& value) {return value; },
	adapter_extent, adapter_extent,
	_T > ;

NGS_LIB_MODULE_END