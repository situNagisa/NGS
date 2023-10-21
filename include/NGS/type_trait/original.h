#pragma once

#include "./defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class _Type>
using original_t = std::remove_cvref_t<_Type>;

NGS_TYPE_TRAIT_END
