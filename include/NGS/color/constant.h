#pragma once

#include "./defined.h"
#include "./concept.h"

NGS_LIB_BEGIN

template<class _T>
struct constant;

template<class _T, class _O = type_traits::object_t<_T>>
concept color_constant =
color<typename _O::color_type> && requires
{
	{ _O::red } -> std::convertible_to<typename _O::color_type>;
	{ _O::green } -> std::convertible_to<typename _O::color_type>;
	{ _O::blue } -> std::convertible_to<typename _O::color_type>;
	{ _O::pink } -> std::convertible_to<typename _O::color_type>;
	{ _O::yellow } -> std::convertible_to<typename _O::color_type>;
	{ _O::cyan } -> std::convertible_to<typename _O::color_type>;
	{ _O::magenta } -> std::convertible_to<typename _O::color_type>;
	{ _O::black } -> std::convertible_to<typename _O::color_type>;
	{ _O::white } -> std::convertible_to<typename _O::color_type>;
	{ _O::gray } -> std::convertible_to<typename _O::color_type>;
	{ _O::dark_gray } -> std::convertible_to<typename _O::color_type>;
	{ _O::light_gray } -> std::convertible_to<typename _O::color_type>;
	{ _O::orange } -> std::convertible_to<typename _O::color_type>;
	{ _O::brown } -> std::convertible_to<typename _O::color_type>;
	{ _O::purple } -> std::convertible_to<typename _O::color_type>;
};

NGS_LIB_END