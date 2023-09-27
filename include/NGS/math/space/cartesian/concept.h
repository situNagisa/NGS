#pragma once

#include "NGS/math/space/base/concept.h"
#include "./defined.h"

NGS_SPACE_CARTESIAN_BEGIN

template<class _Coordinate>
inline constexpr bool _is_cartesian = requires{
	true;
};

template<class _Coordinate>
concept CCartesian = CCoordinate<_Coordinate> && _is_cartesian<std::remove_cvref_t<_Coordinate>>;

NGS_SPACE_CARTESIAN_END
