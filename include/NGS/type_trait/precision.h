#pragma once

#include "./defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class Type> struct  precision { using type = Type; };

template<> struct precision<float> { using type = double; };
template<> struct precision<double> { using type = long double; };
template<> struct precision<int8> { using type = int16; };
template<> struct precision<int16> { using type = int32; };
template<> struct precision<int32> { using type = int64; };
template<> struct precision<uint8> { using type = uint16; };
template<> struct precision<uint16> { using type = uint32; };
template<> struct precision<uint32> { using type = uint64; };

template<class Type>
using precision_t = typename precision<Type>::type;

NGS_TYPE_TRAIT_END
