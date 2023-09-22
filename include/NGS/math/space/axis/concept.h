#pragma once

#include "NGS/math/space/defined.h"

NGS_COORDINATE_BEGIN

template<class _Axis>
inline constexpr bool _is_axis = requires{
	{ _Axis::dimension } -> std::convertible_to<size_t>;
	{ _Axis::sign };
};
template<class _Axis>
concept CAxis = _is_axis<std::remove_cvref_t<_Axis>>;

template<CAxis _Axis, size_t _Dimension>
inline constexpr bool _is_axis_dimension_equal = _Axis::dimension == _Dimension;

template<class _Axis, size_t _Dimension>
concept CAxisDimensionEqual = _is_axis_dimension_equal<std::remove_cvref_t<_Axis>, _Dimension>;

template<class _Axis> concept CAxisX = CAxis<_Axis> && CAxisDimensionEqual<_Axis,0>;
template<class _Axis> concept CAxisY = CAxis<_Axis> && CAxisDimensionEqual<_Axis,1>;
template<class _Axis> concept CAxisZ = CAxis<_Axis> && CAxisDimensionEqual<_Axis,2>;
template<class _Axis> concept CAxisW = CAxis<_Axis> && CAxisDimensionEqual<_Axis,3>;

NGS_COORDINATE_END
