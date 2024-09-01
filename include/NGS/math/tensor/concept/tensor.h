#pragma once

#include "../trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept tensor = ::std::ranges::range<T>
	&& requires
{
	{ traits::shape<T>() } -> external::stl::ranges::algorithm::static_sized_range;
	requires ::std::convertible_to<::std::ranges::range_value_t<decltype(traits::shape<T>())>, ::std::size_t>;
	requires (traits::max_dimension_of_v<T> >= traits::dimension_of<T>());
};

template<class T>
concept vector = tensor<T> && (traits::dimension_of<T>() == 1);

template<class T>
concept matrix = tensor<T> && (traits::dimension_of<T>() == 2);

NGS_LIB_MODULE_END
