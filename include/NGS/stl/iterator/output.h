#pragma once

#include "./input_or_output.h"

NGS_STL_ITERATOR_BEGIN
/**
 * \code
 * std::output_iterator :
 * std::indirectly_writable;
 * requires :
 * *i++ = t;
 * \endcode
*/
/**
 * \brief
 *
 * \tparam _Derived
 * \tparam _Difference
 *
*/
template<
	class _Derived,
	class _Difference = std::ptrdiff_t
>
struct output : input_or_output<_Derived, _Difference>
{
	NGS_MPL_ENVIRON(output);
public:
	using iterator_category = std::output_iterator_tag;

	using base_type::base_type;

	//constexpr auto& operator*();
};

NGS_STL_ITERATOR_END