#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/STL.h"
#include "NGS/base/type_trait.h"
#include "NGS/base/mpl/mpl.h"

NGS_BEGIN
NGS_CONCEPT

template<class T, class U>
concept CSameTemplate = mpl::is_same_template_v<T, U>;

template<class T, template<class...>class _Template>
concept CTemplateFrom = mpl::is_template_v<T, _Template>;

template< class T, class... Types>
concept CSameAsAny = mpl::is_any_of_v<T, Types...>;

template<class T, class _From>
concept CDifferentFrom = (!std::same_as<T, _From>);

template<class T>
concept CIntegral = std::is_integral_v<T>;

template<class T>
concept CUnsignedIntegral = std::is_unsigned_v<T>;

template<class T>
concept CSignedIntegral = std::is_signed_v<T>;

template<class T>
concept CFloatingPoint = std::is_floating_point_v<T>;

template<class T>
concept CArithmetic = std::is_arithmetic_v<T>;

template<class T>
concept CFunction = std::is_function_v<T>;

template<class T>
concept CFundamental = std::is_fundamental_v<T>;


template<class T>
concept _RANL = requires(T t) {
	{ t.IsOpened() } -> std::same_as<bool>;
	{ t.Close() } -> std::same_as<void>;
}
&& std::convertible_to< mpl::function_return_t<decltype(T::Open)>, bool>
;

template<class T, class... Args>
concept CRANL = _RANL<T> && std::invocable<decltype(T::Open), T*, Args...>;

template<class T>
concept CRALL = !_RANL<T>;

NGS_END
NGS_END