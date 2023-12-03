#pragma once

#include "../concept.h"

NGS_BOOST_FUSION_BEGIN

template<class _Type, class _ObjectType = std::remove_reference_t<_Type>>
concept CPair = requires() {
	typename _ObjectType::first_type;
	typename _ObjectType::second_type;
};

NGS_BOOST_FUSION_END