#pragma once

#include "../operator.h"
#include "../extent.h"
#include "../io.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

/// satisfy concept `contiguous_vector` or `output_vector`(when value_type is not const)

template<class, extent_t _Extent = dynamic_extent>
struct vector;

NGS_LIB_MODULE_END

NGS_LIB_MODULE_EXPORT(vector);

NGS_LIB_BEGIN

template<class _T> using vector1 = vector<_T, 1>;
template<class _T>using vector1c = vector<::std::complex<_T>, 1>;

using vector1i = vector1<int>;
using vector1f = vector1<float>;
using vector1d = vector1<double>;
using vector1s = vector1<size_t>;
using vector1ci = vector1c<int>;
using vector1cf = vector1c<float>;
using vector1cd = vector1c<double>;
using vector1cs = vector1c<size_t>;

template<class _T> using vector2 = vector<_T, 2>;
template<class _T>using vector2c = vector<::std::complex<_T>, 2>;

using vector2i = vector2<int>;
using vector2f = vector2<float>;
using vector2d = vector2<double>;
using vector2s = vector2<size_t>;
using vector2ci = vector2c<int>;
using vector2cf = vector2c<float>;
using vector2cd = vector2c<double>;
using vector2cs = vector2c<size_t>;

template<class _T> using vector3 = vector<_T, 3>;
template<class _T>using vector3c = vector<::std::complex<_T>, 3>;

using vector3i = vector3<int>;
using vector3f = vector3<float>;
using vector3d = vector3<double>;
using vector3s = vector3<size_t>;
using vector3ci = vector3c<int>;
using vector3cf = vector3c<float>;
using vector3cd = vector3c<double>;
using vector3cs = vector3c<size_t>;

template<class _T> using vector4 = vector<_T, 4>;
template<class _T>using vector4c = vector<::std::complex<_T>, 4>;

using vector4i = vector4<int>;
using vector4f = vector4<float>;
using vector4d = vector4<double>;
using vector4s = vector4<size_t>;
using vector4ci = vector4c<int>;
using vector4cf = vector4c<float>;
using vector4cd = vector4c<double>;
using vector4cs = vector4c<size_t>;

using vectori = vector<int>;
using vectorf = vector<float>;
using vectord = vector<double>;
//using vectors = vector<size_t>;
using vectorci = vector<::std::complex<int>>;
using vectorcf = vector<::std::complex<float>>;
using vectorcd = vector<::std::complex<double>>;
using vectorcs = vector<::std::complex<size_t>>;

NGS_LIB_END

