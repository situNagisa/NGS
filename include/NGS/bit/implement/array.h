#pragma once

#include "../concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<concepts::range T>
	requires ::std::is_object_v<T>
struct array : ::std::ranges::view_interface<array<T>>
{
	NGS_PP_INJECT_BEGIN(array);
public:

};

NGS_LIB_MODULE_END