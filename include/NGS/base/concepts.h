#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/STL.h"
#include "NGS/base/type_trait.h"

NGS_BEGIN
NGS_CONCEPT

template< class T, class... Types>
concept SameAsAny = _TYT is_any_of<T, Types...>;

template<class T, class _From>
concept DifferentFrom = (!std::same_as<T, _From>);

template<class T>
concept Integral = std::is_integral_v<T>;

template<class T>
concept UnsignedIntegral = std::is_unsigned_v<T>;

template<class T>
concept SignedIntegral = std::is_signed_v<T>;

template<class T>
concept FloatingPoint = std::is_floating_point_v<T>;

template<class T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<class T>
concept Function = std::is_function_v<T>;

template<class T>
concept Fundamental = std::is_fundamental_v<T>;


template<class T>
concept Openable = requires(T t) {
	{ t.IsOpened() } -> std::same_as<bool>;
	{ t.Close() } -> std::same_as<void>;
}
&& std::convertible_to< _TYT function_return_t<decltype(T::Open)>, bool>
;

template<class T, class... Args>
concept OpenableBy = Openable<T> && std::invocable<decltype(T::Open), T*, Args...>;

NGS_END
NGS_END