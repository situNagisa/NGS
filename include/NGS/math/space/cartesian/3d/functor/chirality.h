#pragma once

#include "NGS/math/space/defined.h"
#include "NGS/math/space/cartesian/concept.h"
#include "NGS/math/space/cartesian/support.h"
#include "NGS/math/space/cartesian/3d/defined.h"

NGS_SPACE_CARTESIAN_3D_BEGIN

template<CCartesian _Left, CCartesian _Right>
constexpr bool chirality_is_same_as = requires{
	requires _Left::axes_type::size == _Right::axes_type::size;
	requires _Left::axes_type::size == 3;
	requires (_Left::axes_type::template at_c<0>::sign* _Left::axes_type::template at_c<1>::sign* _Left::axes_type::template at_c<2>::sign) ==
(_Right::axes_type::template at_c<0>::sign * _Right::axes_type::template at_c<1>::sign * _Right::axes_type::template at_c<2>::sign);
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
