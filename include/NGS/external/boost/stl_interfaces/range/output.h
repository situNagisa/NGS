#pragma once

#include "./base.h"

NGS_BOOST_STL_INTERFACES_BEGIN

template<class _Derived, class _AssignRightType, std::output_iterator<_AssignRightType> _Iterator>
struct output_range : base_range<_Derived>
{
	NGS_MPL_ENVIRON(output_range);
public:
	using output_iterator_type = _Iterator;

	constexpr output_iterator_type begin();
	constexpr output_iterator_type end();
};

NGS_BOOST_STL_INTERFACES_END
