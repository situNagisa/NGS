#pragma once

#include "./defined.h"


NGS_LIB_BEGIN

//for ADL, need to be in lib's namespace 

template<static_extent_vector _V>
constexpr extent_t size(_V&&) { return extent_v<_V>; }

NGS_LIB_END