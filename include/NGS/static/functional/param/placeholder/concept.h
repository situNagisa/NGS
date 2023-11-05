#pragma once

#include "./trait.h"
#include "../concept.h"

NGS_STATIC_FUNCTIONAL_BEGIN

template <class _T>
concept is_placeholder = is_param<_T> && requires{ { placeholder_traits<_T>::index } -> std::convertible_to<index_t>; };

NGS_STATIC_FUNCTIONAL_END