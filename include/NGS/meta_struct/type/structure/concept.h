#pragma once

#include "./describe.h"
#include "./storage.h"

NGS_META_STRUCT_TYPE_BEGIN

template<class _Struct>
concept CStructure = CStructureDescribe<_Struct> && CStructureStorage<_Struct>;

NGS_META_STRUCT_TYPE_END
