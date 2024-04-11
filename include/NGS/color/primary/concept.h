#pragma once

#include "../channel.h"
#include "../basic.h"
#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept primary_color = 
	basic::color<T>
	&& channels::arithmetic_channel<primary_alpha_t<T>>
	&& channels::arithmetic_channel<primary_red_t<T>>
	&& channels::arithmetic_channel<primary_green_t<T>>
	&& channels::arithmetic_channel<primary_blue_t<T>>
	&& requires(T color)
{
	{ color.value() }	-> ::std::convertible_to<primary_value_t<T>>;
	{ color.alpha() }	-> ::std::convertible_to<channels::underlying_type_t<primary_alpha_t<T>>>;
	{ color.red()	}	-> ::std::convertible_to<channels::underlying_type_t<primary_red_t<T>>>;
	{ color.green()	}	-> ::std::convertible_to<channels::underlying_type_t<primary_green_t<T>>>;
	{ color.blue()	}	-> ::std::convertible_to<channels::underlying_type_t<primary_blue_t<T>>>;
};

NGS_LIB_MODULE_END