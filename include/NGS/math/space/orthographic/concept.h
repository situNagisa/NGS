#pragma once

#include "NGS/math/space/base/concept.h"

NGS_COORDINATE_BEGIN

template<class _Coordinate>
inline constexpr bool _is_orthographic_coordinate = requires{
	true;
};

template<class _Coordinate>
concept COrthographicCoordinate = CCoordinate<_Coordinate> && _is_orthographic_coordinate<std::remove_cvref_t<_Coordinate>>;

NGS_COORDINATE_END
