#pragma once

#include "../basic.h"
#include "./descriptor.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept storage_structure = basic::structure<struct_descriptor_t<T>> && 
							(sizeof(type_traits::object_t<T>) == variables::variable_size_v<struct_descriptor_t<T>>) && 
							(alignof(type_traits::object_t<T>) == variables::variable_align_v<struct_descriptor_t<T>>);

NGS_LIB_MODULE_END
