#pragma once

#include "./shape.h"
#include "./defined.h"


NGS_LIB_MODULE_BEGIN

template<class T>
struct _dimension_of_functor
{
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()() NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
		requires external::stl::ranges::algorithm::static_sized_range<decltype(shape<T>())>
	{
		return external::stl::ranges::algorithm::static_size<decltype(shape<T>())>();
	}
};

template<class T>
inline constexpr _dimension_of_functor<T> dimension_of{};

NGS_LIB_MODULE_END