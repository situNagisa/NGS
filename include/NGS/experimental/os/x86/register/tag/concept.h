#pragma once

#include "./_all.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept indirectly_writable_tag = general_purpose_register_tag<T>;

NGS_LIB_MODULE_END