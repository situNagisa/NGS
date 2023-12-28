#pragma once

#include "./iterator.h"
#include "./trait.h"

NGS_MATH_VECTOR_BEGIN

template<functor::container _Vector>
constexpr decltype(auto) begin(_Vector& vector) { return io_iterator_t<_Vector>(&vector, 0); }
template<functor::container _Vector>
constexpr decltype(auto) end(_Vector& vector) { return io_iterator_t<_Vector>(&vector, functor::dimension<_Vector>); }
template<functor::expression _Vector>
constexpr decltype(auto) begin(const _Vector& vector) { return in_iterator_t<_Vector>(&vector, 0); }
template<functor::expression _Vector>
constexpr decltype(auto) end(const _Vector& vector) { return in_iterator_t<_Vector>(&vector, functor::dimension<_Vector>); }

template<functor::container _Vector>
constexpr decltype(auto) rbegin(_Vector& vector) { return reverse_io_iterator_t<_Vector>(&vector, vector.size() - 1); }
template<functor::container _Vector>
constexpr decltype(auto) rend(_Vector& vector) { return reverse_io_iterator_t<_Vector>(&vector, -1); }
template<functor::expression _Vector>
constexpr decltype(auto) rbegin(const _Vector& vector) { return reverse_in_iterator_t<_Vector>(&vector, vector.size() - 1); }
template<functor::expression _Vector>
constexpr decltype(auto) rend(const _Vector& vector) { return reverse_in_iterator_t<_Vector>(&vector, -1); }

template<functor::expression _Vector>
constexpr decltype(auto) cbegin(const _Vector& vector) { return begin(vector); }
template<functor::expression _Vector>
constexpr decltype(auto) cend(const _Vector& vector) { return end(vector); }
template<functor::expression _Vector>
constexpr decltype(auto) crbegin(const _Vector& vector) { return rbegin(vector); }
template<functor::expression _Vector>
constexpr decltype(auto) crend(const _Vector& vector) { return rend(vector); }

NGS_MATH_VECTOR_END