#pragma once

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL.h"
#include "NGS/NGS_TypeTrait.h"

NGS_BEGIN
NGS_CONCEPT

template< class T, class... Types>
concept Any = _TYT IsAnyOf<T, Types...>;

template<class Base_, class Derived>
concept Base = _TYT IsBaseOf<Base_, Derived>;

template<class T1, class T2>
concept Same = _TYT IsSame<T1, T2>;

template<class T1, class T2>
concept Different = !Same<T1, T2>;

template<class T>
concept Integral = _TYT IsINT<T>;

template<class T>
concept UnsignedIntegral = _TYT IsUINT<T>;

template<class T>
concept SignedIntegral = !(_TYT IsUINT<T>) && _TYT IsINT<T>;

template<class T>
concept FloatingPoint = _TYT IsFLOAT<T>;

template<class T>
concept Arithmetic = _TYT IsArithmetic<T>;

template<class T>
concept Function = _TYT IsFunction<T>;

NGS_END
NGS_END