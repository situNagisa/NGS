#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

using vectors::extent_t;
using vectors::index_t;
using vectors::difference_t;
//using vectors::extent_v;

using vectors::dynamic_extent;
using vectors::adapter_extent;

template<class _M>
constexpr extent_t major_extent_v = vectors::extent_v<_M>;

template<class _M, class _With>
constexpr extent_t major_static_extent = vectors::static_extent<_M, _With>;

template<class _M>
constexpr extent_t minor_extent_v = vectors::extent_v<::std::ranges::range_value_t<_M>>;

template<class _M, class _With>
constexpr extent_t minor_static_extent = vectors::static_extent<::std::ranges::range_value_t<_M>, ::std::ranges::range_value_t<_With>>;

NGS_LIB_END