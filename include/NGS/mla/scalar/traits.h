#pragma once

#include "NGS/mla/base/traits.h"

NGS_MLA_BEGIN

template<class T>
struct scalar_traits : type_traits<T> {
private:
	using base_type = typename scalar_traits::self_type;
public:
	using self_type = scalar_traits<T>;

	static typename base_type::real_type
		real(typename base_type::const_reference t) { return t; }
};

NGS_MLA_END
