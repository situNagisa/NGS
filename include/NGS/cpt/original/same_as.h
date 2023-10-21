#pragma once

#include "../defined.h"

NGS_CPT_BEGIN

template<class _Left, class _Right>
concept original_same_as = type_traits::is_same_original_v<_Left, _Right>;

NGS_CPT_END