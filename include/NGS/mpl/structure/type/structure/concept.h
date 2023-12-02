#pragma once

#include "./describe.h"
#include "./storage.h"

NGS_LIB_MODULE_BEGIN

template<class _Struct>
concept CStructure = CStructureDescribe<_Struct> && CStructureStorage<_Struct>;

NGS_LIB_MODULE_END
