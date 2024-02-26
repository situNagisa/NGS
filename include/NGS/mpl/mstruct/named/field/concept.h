#pragma once

#include "../../variable.h"
#include "./name.h"
#include "./field.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept named_field = name<named_pair_name_t<T>> && variables::variable<named_pair_field_t<T>>;

NGS_LIB_MODULE_END