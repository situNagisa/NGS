#pragma once

#include "../defined.h"

NGS_CPT_BEGIN

template<class _Left,class _Right>
concept object_same_as = type_traits::is_same_object_v<_Left, _Right>;

NGS_CPT_END