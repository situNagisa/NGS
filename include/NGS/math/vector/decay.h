﻿#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<class _T>
struct decay
{
	using object_type = type_traits::object_t<_T>;
	using type = ::std::conditional_t<sizeof(object_type) <= (2 * sizeof(void*)), object_type, object_type&&>;
};

template<class _T> using decay_t = typename decay<_T>::type;


template<class _T> struct decay<_T&> { using type = _T; };

NGS_LIB_END