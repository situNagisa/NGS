#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept resource = concepts::object<T> && ::std::movable<T>;

template<class>
inline constexpr bool enable_view = true;

template<class T>
concept view = resource<T> && enable_view<T>;

template<class T>
concept viewable_resource = resource<T> && (
	(view<::std::remove_cvref_t<T>> && ::std::constructible_from<::std::remove_cvref_t<T>, T>)
	|| (!view<::std::remove_cvref_t<T>> && (::std::is_lvalue_reference_v<T> || (::std::movable<::std::remove_cvref_t<T>>)))
	);

NGS_LIB_MODULE_END