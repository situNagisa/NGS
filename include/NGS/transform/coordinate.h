#pragma once

#include "NGS/transform/defined.h"

NGS_TRANSFORM_BEGIN

template<class _From, class _To, class _ElementType, class = std::make_index_sequence<_From::axes_type::size>>
struct _coordinate_transform;

template<space::CCoordinate _From, space::CCoordinate _To, mla::CScalarExpression _ElementType, size_t... _Index>
	requires space::CCoordinateDimensionEqaul<_From, _To::axes_type::size>
struct _coordinate_transform<_From, _To, _ElementType, std::index_sequence<_Index...>>
{
	static constexpr auto apply() {
		using element_type = _ElementType;
		using matrix_type = mla::Matrix<_From::axes_type::size, _From::axes_type::size, element_type>;

		matrix_type matrix{};

		((matrix.assign(
			_To::axes_type::template at_c<_Index>::dimension,
			_From::axes_type::template at_c<_Index>::dimension,
			_From::axes_type::template at_c<_Index>::sign /** _To::axes_type::template at_c<_Index>::sign*/
		)), ...);

		return matrix;
	}
};

template<class _From, class _To, class _ElementType>
constexpr auto coordinate_transform() {
	return _coordinate_transform<_From, _To, _ElementType>::apply();
}

NGS_TRANSFORM_END
