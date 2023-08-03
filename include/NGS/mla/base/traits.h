#pragma once

#include "NGS/mla/defined.h"

NGS_MLA_BEGIN

template<ccpt::CRPT _Derived, class T>
struct basic_type_traits {
	using self_type = _Derived;
	using value_type = T;
	using const_reference = const T&;
	using reference = T&;

	using real_type = T;
	using precision_type = real_type;
};

template<class T>
struct type_traits : basic_type_traits<type_traits<T>, T> {};

template<>
struct type_traits<float> : basic_type_traits<type_traits<float>, float> {
	using precision_type = double;
};
template<>
struct type_traits<double> : basic_type_traits<type_traits<double>, double> {
	using precision_type = long double;
};

NGS_MLA_END
