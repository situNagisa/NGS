#pragma once

#include "./defined.h"

NGS_BASIC_TYPE_BEGIN

using void_t = void;
using void_ptr = void*;
using void_ptr_cst = const void*;

//int
NGS_BASIC_TYPE_DEFINE(std::int8_t, int8);
NGS_BASIC_TYPE_DEFINE(std::int16_t, int16);
NGS_BASIC_TYPE_DEFINE(std::int32_t, int32);
NGS_BASIC_TYPE_DEFINE(std::int64_t, int64);

NGS_BASIC_TYPE_DEFINE(std::uint8_t, uint8);
NGS_BASIC_TYPE_DEFINE(std::uint16_t, uint16);
NGS_BASIC_TYPE_DEFINE(std::uint32_t, uint32);
NGS_BASIC_TYPE_DEFINE(std::uint64_t, uint64);

NGS_BASIC_TYPE_DEFINE(std::size_t, size_t);

//float
NGS_BASIC_TYPE_DEFINE(std::float_t, float32);
NGS_BASIC_TYPE_DEFINE(std::double_t, float64);

NGS_BASIC_TYPE_END