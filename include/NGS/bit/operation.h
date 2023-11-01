#pragma once

#include "./defined.h"

NGS_BIT_BEGIN

constexpr size_t bit_per_byte = 8;

template<std::unsigned_integral _Int> constexpr _Int scope(size_t index) { return static_cast<_Int>(1) << index; }
constexpr uint64									 scope(size_t index) { return scope<uint64>(index); }

constexpr size_t as_byte(size_t bit_count) { return (((bit_count) / bit_per_byte) + (((bit_count) % bit_per_byte) > 0)); }
constexpr size_t as_bit(size_t byte_count) { return byte_count * bit_per_byte; }
template<class _T> consteval size_t as_bit() { return as_bit(sizeof(_T)); }

constexpr uint64 mask(std::integral auto bit_count) { return (bit_count >= as_bit<uint64>()) ? static_cast<uint64>(-1) : (scope<uint64>(bit_count) - 1); }

constexpr auto set(auto bit_set, auto bit_scope, bool state) { return state ? bit_set | bit_scope : bit_set & ~bit_scope; }
constexpr auto get(auto bit_set, auto bit_scope) { return bit_set & bit_scope; }


NGS_BIT_END
