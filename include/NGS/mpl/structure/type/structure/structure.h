#pragma once

#include "./concept.h"

NGS_STRUCTURE_TYPE_BEGIN

template<class... _Types>
struct structure : struct_storage<make_describe_t<_Types...>> {};

NGS_STRUCTURE_TYPE_END
