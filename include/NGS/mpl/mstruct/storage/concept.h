#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept storage_structure = basic::structure<T> && 
							(sizeof(type_traits::object_t<T>) == basic::struct_size<T>::value) &&
							(alignof(type_traits::object_t<T>) == basic::struct_align<T>::value.align());

NGS_LIB_MODULE_END
