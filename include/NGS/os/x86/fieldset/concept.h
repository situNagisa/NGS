#pragma once

#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept fieldset = ::std::convertible_to<T, underlying_type_t<T>>&& creatable<T>&& ::std::convertible_to<::std::invoke_result_t<creator<T>,underlying_type_t<T>>, T>;

NGS_LIB_MODULE_END