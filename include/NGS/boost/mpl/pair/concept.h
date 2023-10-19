#pragma once

#include "../defined.h"

NGS_BOOST_MPL_BEGIN

template<class _Type, class _ObjectType = std::remove_reference_t<_Type>>
concept CPair = requires() {
	typename _ObjectType::first;
	typename _ObjectType::second;
};

NGS_BOOST_MPL_END
