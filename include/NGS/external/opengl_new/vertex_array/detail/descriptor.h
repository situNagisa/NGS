#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept buffer_descriptor = mpl::mstruct::flattened_structure<T> && mpl::mstruct::storage_structure<T>;

template<class... Ts>
using descriptor = mpl::mstruct::storage<layout::no_align, Ts...>;

NGS_LIB_MODULE_END