#pragma once

#include "NGS/math/space/defined.h"
#include "NGS/math/space/axis/concept.h"

NGS_SPACE_BEGIN

template<class _Coordinate>
inline constexpr bool _is_coordinate = requires{
	requires mpl::CVector<typename _Coordinate::axes_type>;
};

template<class _Coordinate>
concept CCoordinate = _is_coordinate<std::remove_cvref_t<_Coordinate>>;

template<class _Coordinate,size_t _Dimension>
inline constexpr bool _is_coordinate_dimension_equal = _Coordinate::axes_type::size == _Dimension;

template<class _Coordinate,size_t _Dimension>
concept CCoordinateDimensionEqaul = _is_coordinate_dimension_equal<std::remove_cvref_t<_Coordinate>,_Dimension>;

NGS_SPACE_END
