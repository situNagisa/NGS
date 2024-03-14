#pragma once

#include "./buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept vertex_buffer_descriptor = mpl::mstruct::flattened_structure<T> && mpl::mstruct::storage_structure<T>;

template<class... Ts>
using struct_descriptor = mpl::mstruct::storage<layout::no_align, Ts...>;

using vertex_buffer = buffer<enums::buffer_target::array>;

NGS_LIB_MODULE_END