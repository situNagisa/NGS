#pragma once

#include "../defined.h"

NGS_BOOST_FUSION_BEGIN

template<class _Type, class _ObjectType = std::remove_reference_t<_Type>>
concept CContainer = requires
{
	typename boost::fusion::result_of::begin<_ObjectType>::type;
	typename boost::fusion::result_of::end<_ObjectType>::type;
};

NGS_BOOST_FUSION_END