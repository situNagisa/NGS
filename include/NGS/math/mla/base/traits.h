#pragma once

#include "NGS/math/mla/defined.h"

NGS_MLA_BEGIN

template<class T>
struct type_traits {
	using self_type = type_traits<T>;
	using value_type = T;
	using const_reference = const T&;
	using reference = T&;

	using real_type = T;
};

NGS_MLA_END
