#pragma once

#include "./internal.h"
#include "./defined.h"

NGS_LIB_BEGIN

template<class _T>
concept box = vectors::static_extent_vector<_T> && cpt::naked_same_as<vectors::value_t<_T>, internal<typename vectors::value_t<_T>::value_type>>;

NGS_LIB_END