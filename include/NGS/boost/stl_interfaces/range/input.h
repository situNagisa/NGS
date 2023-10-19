#pragma once

#include "./base.h"

NGS_BOOST_STL_INTERFACES_BEGIN

template<class _Derived, std::input_iterator _Iterator>
struct input_range : base_range<_Derived>
{
	NGS_MPL_ENVIRON(input_range);
public:
	using input_iterator_type = _Iterator;

	constexpr auto cbegin()const { return base_type::_derived().begin(); }
	constexpr auto cend()const { return base_type::_derived().end(); }
};

NGS_BOOST_STL_INTERFACES_END
