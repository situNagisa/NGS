#pragma once

#include "NGS/coordinate/defined.h"
#include "NGS/coordinate/axis/concept.h"

NGS_COORDINATE_BEGIN

template<class _Coordinate>
inline constexpr bool _is_coordinate = requires{
	true;
};

template<class _Coordinate>
concept CCoordinate = _is_coordinate<std::remove_cvref_t<_Coordinate>>;

NGS_COORDINATE_END
