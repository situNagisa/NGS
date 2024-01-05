#pragma once

#include "NGS/math/mla/base/traits.h"

NGS_MLA_BEGIN

template<class  T>
struct NGS_DLL_API scalar_traits : type_traits<T> {
private:
	using base_type = typename scalar_traits::self_type;
public:
	using self_type = scalar_traits<T>;

	using precision_type = typename base_type::real_type;
};

template<>
struct NGS_DLL_API scalar_traits<float> : type_traits<float> {
private:
	using base_type = typename scalar_traits::self_type;
public:
	using self_type = scalar_traits<float>;

	using precision_type = double;
};

template<>
struct NGS_DLL_API scalar_traits<double> : type_traits<double> {
private:
	using base_type = typename scalar_traits::self_type;
public:
	using self_type = scalar_traits<double>;

	using precision_type = long double;
};

NGS_MLA_END
