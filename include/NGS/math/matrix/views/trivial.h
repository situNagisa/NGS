#pragma once

#include "./transform.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _T>
using trivial_matrix = transform_view < adapter_extent, adapter_extent,
	[](index_t, index_t, auto&& value) {return value; },
	default_major_sizer<adapter_extent>(), default_minor_sizer<adapter_extent>(), _T > ;

NGS_LIB_MODULE_END