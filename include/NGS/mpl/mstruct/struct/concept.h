#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept storage_structure = basic::structure<T> && 
							(sizeof(type_traits::object_t<T>) == variables::variable_size_v<T>) && 
							(alignof(type_traits::object_t<T>) == variables::variable_align_v<T>);

NGS_LIB_MODULE_END
