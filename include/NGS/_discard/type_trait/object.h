#pragma once

#include "./defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class Type>
using object_t = std::remove_reference_t<Type>;

NGS_TYPE_TRAIT_END
