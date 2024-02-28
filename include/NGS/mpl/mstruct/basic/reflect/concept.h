#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T,class TestType = void>
concept reflecter = requires
{
	{ type_traits::object_t<T>::template reflect<TestType>::value } -> ::std::convertible_to<typename type_traits::object_t<T>::type>;
};

NGS_LIB_MODULE_END