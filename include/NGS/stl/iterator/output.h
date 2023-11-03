#pragma once

#include "./input_or_output.h"

NGS_STL_ITERATOR_BEGIN
/**
 * \brief
 *
 * \tparam _Derived
 * \tparam _Difference
 * \note 要求`_Derived`具有以下成员函数
 * \code
 * iterator_type& _increment()
 * reference auto _dereference()const
 * auto _assign(any auto&& value)
 * \endcode
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

	///\code std::output_iterator\endcode
	using base_type::operator=;
	constexpr decltype(auto) operator=(auto&& value)const { base_type::_derived()._assign(NGS_PP_PERFECT_FORWARD(value)); }
};

NGS_STL_ITERATOR_END