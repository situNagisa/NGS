#pragma once

#include "./scalar.h"
#include "./vector.h"
#include "./matrix.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept uniform = scalar<T> || vector<T> || matrix<T>;

NGS_LIB_MODULE_END
