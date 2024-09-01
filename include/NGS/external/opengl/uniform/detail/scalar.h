#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept scalar = reflects::buffers::uniform_reflectable<T>;

NGS_LIB_MODULE_END