#pragma once

#include "NGS/math/space/orthographic/concept.h"

NGS_COORDINATE_BEGIN

template<class _Coordinate>
inline constexpr bool _is_direction_coordinate = requires{
	requires CAxis<typename _Coordinate::front_type>;
	requires CAxis<typename _Coordinate::right_type>;
	requires CAxis<typename _Coordinate::up_type>;
};

template<class _Coordinate>
concept CDirectionCoordinate = COrthographicCoordinate<_Coordinate> && _is_direction_coordinate<std::remove_cvref_t<_Coordinate>>;

NGS_COORDINATE_END
