#pragma once

#include "NGS/math/space/cartesian/concept.h"
#include "NGS/math/space/cartesian/3d/defined.h"

NGS_SPACE_CARTESIAN_3D_BEGIN

template<class _Coordinate>
inline constexpr bool _is_direction = requires{
	requires CAxis<typename _Coordinate::front_type>;
	requires CAxis<typename _Coordinate::right_type>;
	requires CAxis<typename _Coordinate::up_type>;
};

template<class _Coordinate>
concept CDirection = CCartesian<_Coordinate> && _is_direction<std::remove_cvref_t<_Coordinate>>;

NGS_SPACE_CARTESIAN_3D_END
