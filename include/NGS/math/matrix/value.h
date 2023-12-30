#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<class _M>
using matrix_value_t = ::std::conditional_t<
	::std::ranges::range<_M>&& ::std::ranges::range<::std::ranges::range_value_t<_M>>,
	::std::ranges::range_value_t<::std::ranges::range_value_t<_M>>,
	void
>;

NGS_LIB_END