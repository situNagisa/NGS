#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept fundamental = NGS_EXTERNAL_OPENGL_BASIC_REFLECT_NS::buffer_uniform<T>;

NGS_LIB_MODULE_END