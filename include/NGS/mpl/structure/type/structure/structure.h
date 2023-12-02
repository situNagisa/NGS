#pragma once

#include "./concept.h"

NGS_LIB_MODULE_BEGIN

template<class... _Types>
struct structure : struct_storage<make_describe_t<_Types...>> {};

NGS_LIB_MODULE_END
