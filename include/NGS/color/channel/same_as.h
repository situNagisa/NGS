#pragma once

#include "./concept.h"

NGS_LIB_MODULE_BEGIN

template<class _Left, class _Right, class _L = type_traits::object_t<_Left>, class _R = type_traits::object_t<_Right>>
concept same_as = color_channel<_Left> && color_channel<_Right>
&& (_L::count == _R::count)
&& (_L::offset == _R::offset)
&& (_L::filter == _R::filter)
&& (_L::filter_with_offset == _R::filter_with_offset)
&& ::std::same_as<typename _L::type, typename _R::type>;

NGS_LIB_MODULE_END