#pragma once

#include "./decay.h"

NGS_LIB_BEGIN

template<class _T>
struct param_trait
{
	using type = _T;
	using object = type_traits::object_t<type>;
	using decay = decay_t<type>;
	using value = type_traits::object_t<decay>;
	using pointer = ::std::add_pointer_t<type_traits::object_t<decay>>;
	using const_pointer = ::std::add_pointer_t<::std::add_const_t<type_traits::object_t<decay>>>;
	using param = ::std::conditional_t<::std::is_reference_v<decay>, decay, type_traits::add_cvref_like_t<const int&, object>>;
};


NGS_LIB_END