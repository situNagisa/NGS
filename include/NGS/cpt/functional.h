#pragma once

#include "./defined.h"

NGS_CPT_BEGIN

template<class _Functor, class _Result, class... _Args>
concept invocable_and_result_same_as = ::std::invocable<_Functor, _Args...>&& ::std::same_as<::std::invoke_result_t<_Functor, _Args...>, _Result>;

template<class _Functor, class _Result, class... _Args>
concept invocable_and_result_convertible_to = ::std::invocable<_Functor, _Args...>&& ::std::convertible_to<::std::invoke_result_t<_Functor, _Args...>, _Result>;

NGS_CPT_END