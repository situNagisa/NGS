#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept align = requires(const T obj)
{
	{ obj.priority() } -> ::std::convertible_to<::std::size_t>;
	{ obj.align() } -> ::std::convertible_to<::std::size_t>;
};

NGS_LIB_MODULE_END
