#pragma once

#include "./extent.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _L, class _R>
concept similar_vector = same_extent<_L, _R>&& ::std::common_reference_with<value_t<_L>&, value_t<_R>&>;

NGS_LIB_MODULE_END
