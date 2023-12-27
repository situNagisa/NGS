#pragma once

#include "./defined.h"

#define NGS_EXTERN_STL_RANGE_INPUT_ITERATOR()										\
	constexpr auto rbegin() const { return ::std::make_reverse_iterator(end()); }	\
	constexpr auto rend() const { return ::std::make_reverse_iterator(begin()); }	\
	constexpr auto cbegin() const { return begin(); }								\
	constexpr auto cend() const { return end(); }									\
	constexpr auto crbegin() const { return rbegin(); }								\
	constexpr auto crend() const { return rend(); }									\
//

#define NGS_EXTERN_STL_RANGE_OUTPUT_ITERATOR()										\
	constexpr auto rbegin() { return ::std::make_reverse_iterator(end()); }			\
	constexpr auto rend() { return ::std::make_reverse_iterator(begin()); }			\
//

#define NGS_EXTERN_STL_RANGE_INPUT_AND_OUTPUT_ITERATOR()\
	NGS_EXTERN_STL_RANGE_INPUT_ITERATOR()				\
	NGS_EXTERN_STL_RANGE_OUTPUT_ITERATOR()				\
//

