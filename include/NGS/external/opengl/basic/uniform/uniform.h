#pragma once

#include "./fundamental.h"
#include "./vector.h"
#include "./matrix.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept uniform = fundamental<T> || vector<T> || matrix<T>;

NGS_LIB_MODULE_END
