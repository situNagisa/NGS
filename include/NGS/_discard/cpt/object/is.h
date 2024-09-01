#pragma once

#include "../defined.h"

NGS_CPT_BEGIN

template<class _T>
concept is_object = std::is_object_v<_T>;

NGS_CPT_END