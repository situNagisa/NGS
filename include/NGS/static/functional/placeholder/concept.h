#pragma once

#include "./trait.h"

NGS_FUNCTIONAL_BEGIN

template <class _T>
concept is_placeholder = requires{ { arg_traits<_T>::index } -> std::convertible_to<arg_index_t>; };

NGS_FUNCTIONAL_END