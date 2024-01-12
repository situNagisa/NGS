#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

using depth_t = size_t;

inline constexpr depth_t invalid_depth = static_cast<depth_t>(-1);

template<class>
struct depth : ccpt::constant_<depth_t, 0> {};

///\brief get the recurse depth of a vector 
///\note witch is the number of vector in the vector 
///\code
///depth_v<vector<vector<int>>> == 2
///\endcode
template<class _V>
inline constexpr depth_t depth_v = depth<_V>::value;

NGS_LIB_END