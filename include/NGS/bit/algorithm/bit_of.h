#pragma once

#include "./bit_byte.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
constexpr ::std::size_t byte_of() noexcept { return sizeof(T); }

template<class T>
constexpr ::std::size_t bit_of() noexcept { return NGS_LIB_MODULE_NAME::byte_to_bit(NGS_LIB_MODULE_NAME::byte_of<T>()); }

NGS_LIB_MODULE_END