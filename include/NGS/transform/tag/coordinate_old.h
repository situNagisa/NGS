#pragma once

#include "NGS/transform/tag/chirality.h"
#include "NGS/transform/tag/axis.h"
#include "NGS/transform/defined.h"

NGS_TRANSFORM_BEGIN

namespace tag {
template<
	CAxis _Front,
	CAxis _Right,
	CAxis _Up,
	CChirality _Chirality>
struct coordinate {
	using front = _Front;
	using right = _Right;
	using up = _Up;

	using chirality_type = _Chirality;
};

template<CAxis _Front, CAxis _Right, CAxis _Up>
struct coordinate_left_half : coordinate <_Front, _Right, _Up, left_half> {};

template<CAxis _Front, CAxis _Right, CAxis _Up>
struct coordinate_right_half : coordinate <_Front, _Right, _Up, right_half> {};


#define NGS_TRANSFORM_DEFINE_COORDINATE(_front,_right,_up)				\
template<mla::CScalarExpression _ElementType>							\
struct coordinate_left_half_##_front##_##_right##_##_up : coordinate_left_half <\
	_front<_ElementType>,												\
	_right<_ElementType>,												\
	_up<_ElementType>> {};												\
template<mla::CScalarExpression _ElementType>							\
struct coordinate_right_half_##_front##_##_right##_##_up : coordinate_right_half <\
	_front<_ElementType>,												\
	_right<_ElementType>,												\
	_up<_ElementType>> {};												\
using coordinate_left_half_##_front##_##_right##_##_up##_i = coordinate_left_half_##_front##_##_right##_##_up<int>;		  \
using coordinate_right_half_##_front##_##_right##_##_up##_i = coordinate_right_half_##_front##_##_right##_##_up<int>;	  \
using coordinate_left_half_##_front##_##_right##_##_up##_f = coordinate_left_half_##_front##_##_right##_##_up<float>;	  \
using coordinate_right_half_##_front##_##_right##_##_up##_f = coordinate_right_half_##_front##_##_right##_##_up<float>;	  \
using coordinate_left_half_##_front##_##_right##_##_up##_d = coordinate_left_half_##_front##_##_right##_##_up<double>;	  \
using coordinate_right_half_##_front##_##_right##_##_up##_d = coordinate_right_half_##_front##_##_right##_##_up<double>;  \
//

NGS_TRANSFORM_DEFINE_COORDINATE(x, y, z);
NGS_TRANSFORM_DEFINE_COORDINATE(x, z, y);
NGS_TRANSFORM_DEFINE_COORDINATE(y, x, z);
NGS_TRANSFORM_DEFINE_COORDINATE(y, z, x);
NGS_TRANSFORM_DEFINE_COORDINATE(z, x, y);
NGS_TRANSFORM_DEFINE_COORDINATE(z, y, x);

#undef NGS_TRANSFORM_DEFINE_COORDINATE
}

template<class _Tag>
inline constexpr bool _is_coordinate = requires{
	{ _Tag::front } -> mla::CVectorDimensionEqual<3>;
	{ _Tag::right } -> mla::CVectorDimensionEqual<3>;
	{ _Tag::up } -> mla::CVectorDimensionEqual<3>;
		requires CChirality<typename _Tag::chirality_type>;
};
template<class _Tag>
concept CCoordinate = _is_coordinate<std::remove_cvref_t<_Tag>>;

NGS_TRANSFORM_END
