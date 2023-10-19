#pragma once

#include "./describe.h"
#include "./storage.h"

NGS_STRUCTURE_TYPE_BEGIN

template<class _Struct>
concept CStructure = CStructureDescribe<_Struct> && CStructureStorage<_Struct>;

NGS_STRUCTURE_TYPE_END
