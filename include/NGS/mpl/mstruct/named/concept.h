#pragma once

#include "../struct.h"
#include "./named_fields.h"
#include "./field.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept named_structure = structs::storage_structure<T> && named_fields<struct_named_fields_t<T>>;

NGS_LIB_MODULE_END