#pragma once

#include "./address.h"
#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept basic_iic = ::std::copyable<iic_value_t<T>> && ::std::is_standard_layout_v<iic_value_t<T>> && (address<iic_address_t<T>, address_width::_7> || address<iic_address_t<T>, address_width::_10>);

template<class T>
concept master = basic_iic<T>
	&& requires (T t, iic_address_t<T> address)
{
	{ connect(NGS_PP_PERFECT_FORWARD(t), address) };
	{ ack_policy(NGS_PP_PERFECT_FORWARD(t)) };
};

template<class T>
concept slave = 
	basic_iic<T>
	&& ::std::convertible_to<decltype(iic_address_width_v<T>), address_width>
	&& requires (T t)
{
	{ current_address(NGS_PP_PERFECT_FORWARD(t)) } -> address<iic_address_width_v<T>>;
};

template<class T>
concept iic = master<T> || slave<T>;

template<class T>
concept input_iic = iic<T>
	&& requires(T t, iic_value_t<T> result)
{
	{ read(NGS_PP_PERFECT_FORWARD(t), NGS_PP_PERFECT_FORWARD(result)) } -> ::std::convertible_to<bool>;
};

template<class T>
concept output_iic = iic<T>
	&& requires(T t, iic_value_t<T> value)
{
	{ write(NGS_PP_PERFECT_FORWARD(t), NGS_PP_PERFECT_FORWARD(value)) } -> ::std::convertible_to<bool>;
};

template<class T>
concept input_and_output_iic = input_iic<T> && output_iic<T>;

template<class T>
concept input_or_output_iic = input_iic<T> || output_iic<T>;

NGS_LIB_MODULE_END