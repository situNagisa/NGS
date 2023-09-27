#pragma once

#include "NGS/math/space/cartesian/concept.h"
#include "NGS/math/space/cartesian/3d/defined.h"

NGS_SPACE_CARTESIAN_3D_BEGIN

template<class _Coordinate>
inline constexpr bool _is_screen = requires{
	requires CAxis<typename _Coordinate::horizontal_type>;
	requires CAxis<typename _Coordinate::vertical_type>;
	requires CAxis<typename _Coordinate::depth_type>;
};

template<class _Coordinate>
concept CScreen = CCartesian<_Coordinate> && _is_screen<std::remove_cvref_t<_Coordinate>>;

NGS_SPACE_CARTESIAN_3D_END
