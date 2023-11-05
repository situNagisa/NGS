#pragma once

#include "./concept.h"

NGS_STATIC_FUNCTIONAL_BEGIN

template<is_packer _Pack, class _O = type_traits::object_t<_Pack>>
constexpr size_t packer_size = _O::count;

NGS_STATIC_FUNCTIONAL_END