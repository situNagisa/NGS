#pragma once

#include "../defined.h"

NGS_BOOST_STL_INTERFACES_BEGIN

template<class _Derived>
struct base_range
{
protected:
	using self_type = base_range;
public:
	using range_type = _Derived;

protected:
	constexpr range_type& _derived() noexcept
	{
		return static_cast<range_type&>(*this);
	}
	constexpr const range_type& _derived() const noexcept
	{
		return static_cast<const range_type&>(*this);
	}
};

NGS_BOOST_STL_INTERFACES_END
