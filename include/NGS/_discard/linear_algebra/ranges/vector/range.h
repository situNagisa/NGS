#pragma once

#include "./iterator.h"

NGS_MATH_LA_VECTOR_RANGE_BEGIN

template<concepts::vectors::output_wrapper _T>
constexpr decltype(auto) begin(_T& vector) { return input_or_output_iterator_t<_T>(&vector, 0); }
template<concepts::vectors::output_wrapper _T>
constexpr decltype(auto) end(_T& vector) { return input_or_output_iterator_t<_T>(&vector, adapters::vectors::dimension(vector)); }
template<concepts::vectors::expression _T>
constexpr decltype(auto) begin(const _T& vector) { return input_iterator_t<const _T>(&vector, 0); }
template<concepts::vectors::expression _T>
constexpr decltype(auto) end(const _T& vector) { return input_iterator_t<const _T>(&vector, adapters::vectors::dimension(vector)); }

template<concepts::vectors::output_wrapper _T>
constexpr decltype(auto) rbegin(_T& vector) { return input_or_output_reverse_iterator_t<_T>(&vector, adapters::vectors::dimension(vector) - 1); }
template<concepts::vectors::output_wrapper _T>
constexpr decltype(auto) rend(_T& vector) { return input_or_output_reverse_iterator_t<_T>(&vector, -1); }
template<concepts::vectors::expression _T>
constexpr decltype(auto) rbegin(const _T& vector) { return input_reverse_iterator_t<const _T>(&vector, adapters::vectors::dimension(vector) - 1); }
template<concepts::vectors::expression _T>
constexpr decltype(auto) rend(const _T& vector) { return input_reverse_iterator_t<const _T>(&vector, -1); }

template<concepts::vectors::expression _T>
constexpr decltype(auto) cbegin(const _T& vector) { return begin(vector); }
template<concepts::vectors::expression _T>
constexpr decltype(auto) cend(const _T& vector) { return end(vector); }
template<concepts::vectors::expression _T>
constexpr decltype(auto) crbegin(const _T& vector) { return rbegin(vector); }
template<concepts::vectors::expression _T>
constexpr decltype(auto) crend(const _T& vector) { return rend(vector); }

NGS_MATH_LA_VECTOR_RANGE_END

//for ADL
NGS_MATH_LA_VECTOR_CONTAINER_BEGIN
using ranges::vectors::begin;
using ranges::vectors::end;
using ranges::vectors::rbegin;
using ranges::vectors::rend;
using ranges::vectors::cbegin;
using ranges::vectors::cend;
using ranges::vectors::crbegin;
using ranges::vectors::crend;
NGS_MATH_LA_VECTOR_CONTAINER_END