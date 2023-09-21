#pragma once

#include "NGS/coordinate/orthographic/concept.h"

NGS_COORDINATE_BEGIN

template<class _Coordinate>
inline constexpr bool _is_screen_coordinate = requires{
	requires CAxis<typename _Coordinate::herizontal_type>;
	requires CAxis<typename _Coordinate::vertial_type>;
	requires CAxis<typename _Coordinate::depth_type>;
};

template<class _Coordinate>
concept CScreenCoordinate = COrthographicCoordinate<_Coordinate> && _is_screen_coordinate<std::remove_cvref_t<_Coordinate>>;

NGS_COORDINATE_END
