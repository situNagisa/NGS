#pragma once

#include "../concept.h"

NGS_BOOST_FUSION_BEGIN

template<class _Type, class _ObjectType = std::remove_reference_t<_Type>>
concept CVector = true;

NGS_BOOST_FUSION_END
