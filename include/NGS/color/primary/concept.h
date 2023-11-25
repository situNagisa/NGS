#pragma once

#include "./trait.h"
#include "../concept.h"

NGS_COLOR_BEGIN

template<class _T, class _O = type_traits::object_t<_T>>
concept CPrimary = CColor<_T> &&
CChannel<typename primary_traits<_T>::alpha_type> &&
CChannel<typename primary_traits<_T>::red_type> &&
CChannel<typename primary_traits<_T>::green_type> &&
CChannel<typename primary_traits<_T>::blue_type> && requires(_T color)
{
	typename _O::type;
	{ color.alpha() } -> std::convertible_to<typename primary_traits<_T>::alpha_type::type>;
	{ color.red() } -> std::convertible_to<typename primary_traits<_T>::red_type::type>;
	{ color.green() } -> std::convertible_to<typename primary_traits<_T>::green_type::type>;
	{ color.blue() } -> std::convertible_to<typename primary_traits<_T>::blue_type::type>;
};

NGS_COLOR_END