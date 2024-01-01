#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<is_packer _Pack, class _O = type_traits::object_t<_Pack>>
constexpr size_t packer_size = _O::count;

NGS_LIB_MODULE_END
NGS_LIB_MODULE_EXPORT(packer_size);