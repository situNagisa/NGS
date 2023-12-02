#pragma once

#include "./structure.h"

NGS_LIB_MODULE_BEGIN

template<CStructure _Struct>
constexpr auto&& wrapper(void_ptr address) {
	return *static_cast<_Struct*>(address);
}

template<CStructure _Struct>
constexpr auto&& wrapper(void_ptr_cst address) {
	return *static_cast<const _Struct*>(address);
}

NGS_LIB_MODULE_END
