#pragma once

#include "NGS/math/space/orthographic/concept.h"
#include "NGS/math/space/defined.h"

NGS_COORDINATE_BEGIN

template<class _Coordinate>
inline constexpr bool _is_screen_coordinate = requires{
	requires CAxis<typename _Coordinate::horizontal_type>;
	requires CAxis<typename _Coordinate::vertical_type>;
	requires CAxis<typename _Coordinate::depth_type>;
};

template<class _Coordinate>
concept CScreenCoordinate = COrthographicCoordinate<_Coordinate> && _is_screen_coordinate<std::remove_cvref_t<_Coordinate>>;

NGS_COORDINATE_END
