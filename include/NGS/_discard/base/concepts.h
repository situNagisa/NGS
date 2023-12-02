#pragma once

#include "NGS/base/defined.h"

NGS_BEGIN
NGS_CONCEPT


template<class  T, class  U>
concept CSameTemplate = mpl::is_same_template_v<T, U>;

using mpl::CTemplateFrom;

template< class  _ExpectType, class ... _Types>
concept CSameAsAny = mpl::is_same_with_any_of_v<_ExpectType, _Types...>;

template<class  T, class  _From>
concept CDifferentFrom = (!std::same_as<T, _From>);

template<class  T>
concept CIntegral = std::is_integral_v<T>;

template<class  T>
concept CUnsignedIntegral = std::is_unsigned_v<T>;

template<class  T>
concept CSignedIntegral = std::is_signed_v<T>;

template<class  T>
concept CFloatingPoint = std::is_floating_point_v<T>;

template<class  T>
concept CArithmetic = std::is_arithmetic_v<T>;

//exp
template<class  T>
concept CPseudoArithmetic = CArithmetic<T>;

template<class  T>
concept CFunction = std::is_function_v<T>;

template<class  T>
concept CFundamental = std::is_fundamental_v<T>;


template<class  T>
concept _RANL = requires(T t) {
	{ t.IsOpened() } -> std::same_as<bool>;
	{ t.Close() } -> std::same_as<void>;
}
&& std::convertible_to<typename mpl::function_trait<decltype(T::Open)>::return_type, bool>
;

template<class  T, class ... Args>
concept CRANL = _RANL<T> && std::invocable<decltype(T::Open), T*, Args...>;

template<class  T>
concept CRALL = !_RANL<T>;

NGS_END
NGS_END