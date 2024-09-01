#pragma once

#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<experimental::templates::pure_type_template Tuple, class = ::std::make_index_sequence<size_v<Tuple>>>
struct check_tuple_args : ::std::false_type {};

template<experimental::templates::pure_type_template Tuple, ::std::size_t... I>
struct check_tuple_args<Tuple, ::std::index_sequence<I...>>
	: ::std::bool_constant<
	((::std::same_as<::std::add_lvalue_reference_t<element_t<I, Tuple>>&&, ::std::invoke_result_t<decltype(get<I>),::std::add_lvalue_reference_t<Tuple>>>) && ...)
> {};

template<class T>
concept tuple = experimental::templates::pure_type_template<::std::remove_cvref_t<T>> && check_tuple_args<::std::remove_cvref_t<T>>::value;

NGS_LIB_MODULE_END