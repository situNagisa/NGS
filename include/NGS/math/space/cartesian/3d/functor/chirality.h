#pragma once

#include "NGS/math/space/defined.h"
#include "NGS/math/space/cartesian/concept.h"
#include "NGS/math/space/cartesian/support.h"
#include "NGS/math/space/cartesian/3d/defined.h"

NGS_SPACE_CARTESIAN_3D_BEGIN

template<CCartesian _Left, CCartesian _Right>
constexpr bool chirality_is_same_as = requires{
	requires boost::fusion::result_of::size<typename _Left::axes_type>::value == boost::fusion::result_of::size<typename _Right::axes_type>::value;
	requires boost::fusion::result_of::size<typename _Left::axes_type>::value == 3;
	requires
	( boost::fusion::result_of::value_at_c<typename _Left::axes_type, 0>::type::sign
	* boost::fusion::result_of::value_at_c<typename _Left::axes_type, 1>::type::sign
	* boost::fusion::result_of::value_at_c<typename _Left::axes_type, 2>::type::sign) ==
	( boost::fusion::result_of::value_at_c<typename _Left::axes_type, 0>::type::sign
	* boost::fusion::result_of::value_at_c<typename _Left::axes_type, 1>::type::sign
	* boost::fusion::result_of::value_at_c<typename _Left::axes_type, 2>::type::sign);
};

template<CCartesian _Coordinate>
constexpr bool is_standard_chirality = requires{
	requires chirality_is_same_as<_Coordinate, standard_coordinate>;
};

template<CCartesian _Coordinate>
constexpr bool is_right_hand = (chirality::standard == chirality::right && is_standard_chirality<_Coordinate>) || (chirality::standard == chirality::left && !is_standard_chirality<_Coordinate>);

template<CCartesian _Coordinate>
constexpr bool is_left_hand = (chirality::standard == chirality::left && is_standard_chirality<_Coordinate>) || (chirality::standard == chirality::right && !is_standard_chirality<_Coordinate>);

NGS_SPACE_CARTESIAN_3D_END
