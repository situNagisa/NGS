#pragma once

#include "./trait.h"
#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<tensor T, class Indices = ::std::array<shapes::shape_index_t<tensor_extents_t<T>>, shapes::rank(shapes::shape_ranks_v<T>)>>
using tensor_value_t = ::std::invoke_result_t<decltype(access), T, Indices>;

NGS_LIB_MODULE_END