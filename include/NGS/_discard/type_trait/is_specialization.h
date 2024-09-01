#pragma once

#include "./naked.h"
#include "./defined.h"

NGS_TYPE_TRAIT_BEGIN
namespace detail
{
	template<class, template<class...>class>
	struct is_specialization : std::false_type {};

	template<template<class...>class Template, class... Types>
	struct is_specialization<Template<Types...>, Template> : std::true_type {};
}

template<class T, template<class...>class Template>
struct is_specialization : detail::is_specialization<naked_t<T>, Template> {};

template<class T, template<class...>class Template>
inline constexpr bool is_specialization_v = is_specialization<T, Template>::value;

namespace detail
{
	template <template <class...> class Template, class... Args>
	void derived_from_specialization(const Template<Args...>&);
}

template <class T, template <class...> class Template>
inline constexpr bool is_derived_from_specialization_v = requires(const T & obj) { detail::derived_from_specialization<Template>(obj); };

template <class T, template <class...> class Template>
struct is_derived_from_specialization : std::bool_constant<is_derived_from_specialization_v<T, Template>> {};


NGS_TYPE_TRAIT_END