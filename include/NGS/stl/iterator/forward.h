#pragma once

#include "./input.h"

NGS_STL_ITERATOR_BEGIN
/**
 * \brief
 * \tparam _Derived
 * \tparam _ValueType
 * \tparam _Difference
*/
template<
	class _Derived,
	class _ValueType,
	class _Difference = std::ptrdiff_t
>
struct forward : input<_Derived, _ValueType, _Difference>
{
	NGS_MPL_ENVIRON(forward);
public:
	NGS_MPL_INHERIT_TYPE(iterator_type, base_type);

	using base_type::base_type;

	///\code std::input_iterator \endcode

};

NGS_STL_ITERATOR_END