#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<class NakedType>
constexpr auto pointer_cast(auto* ptr)
{
	using value_type = type_traits::object_t<::std::remove_pointer_t<decltype(ptr)>>;
	return reinterpret_cast<type_traits::add_cv_like_t<value_type, NakedType>*>(ptr);
}

NGS_LIB_END