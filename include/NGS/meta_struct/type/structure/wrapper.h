#pragma once

#include "./structure.h"

NGS_META_STRUCT_TYPE_BEGIN

template<CStructure _Struct>
constexpr auto& wrapper(void_ptr address) {
	return *static_cast<_Struct*>(address);
}

NGS_META_STRUCT_TYPE_END
