#pragma once

#include "./defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class Type> struct  precision { using type = Type; };

template<> struct precision<float> { using type = double; };
template<> struct precision<double> { using type = long double; };
template<> struct precision<::std::int8_t> { using type = ::std::int16_t; };
template<> struct precision<::std::int16_t> { using type = ::std::int32_t; };
template<> struct precision<::std::int32_t> { using type = ::std::int64_t; };
template<> struct precision<::std::uint8_t> { using type = ::std::uint16_t; };
template<> struct precision<::std::uint16_t> { using type = ::std::uint32_t; };
template<> struct precision<::std::uint32_t> { using type = ::std::uint64_t; };

template<class Type>
using precision_t = typename precision<Type>::type;

NGS_TYPE_TRAIT_END
