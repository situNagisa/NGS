#pragma once

#include "./defined.h"

NGS_CPT_BEGIN

template<class _T>
concept is_template = type_traits::is_template_v<_T>;

NGS_CPT_END