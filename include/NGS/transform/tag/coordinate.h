#pragma once

#include "NGS/transform/tag/axis.h"
#include "NGS/transform/defined.h"

NGS_TRANSFORM_BEGIN

namespace tag {
template<CAxis _Front, CAxis _Right, CAxis _Up>
struct coordinate {
	using front_type = _Front;
	using right_type = _Right;
	using up_type = _Up;

	using element_type = mpl::promote_t<
		typename front_type::element_type,
		typename right_type::element_type,
		typename up_type::element_type>;
};

inline namespace coordinates {
#define NGS_TRANSFORM_DEFINE_COORDINATE(_front,_right,_up)				\
template<mla::CScalarExpression _ElementType>							\
struct coordinate_##_front##_##_right##_##_up : coordinate <			\
	_front<_ElementType>,												\
	_right<_ElementType>,												\
	_up<_ElementType>> {};												\
using coordinate_##_front##_##_right##_##_up##_i = coordinate_##_front##_##_right##_##_up<int>;		  \
using coordinate_##_front##_##_right##_##_up##_f = coordinate_##_front##_##_right##_##_up<float>;	  \
using coordinate_##_front##_##_right##_##_up##_d = coordinate_##_front##_##_right##_##_up<double>;	  \
//

NGS_TRANSFORM_DEFINE_COORDINATE(x, y, z);
NGS_TRANSFORM_DEFINE_COORDINATE(x, y, mz);
NGS_TRANSFORM_DEFINE_COORDINATE(x, my, z);
NGS_TRANSFORM_DEFINE_COORDINATE(x, my, mz);
NGS_TRANSFORM_DEFINE_COORDINATE(x, z, y);
NGS_TRANSFORM_DEFINE_COORDINATE(x, z, my);
NGS_TRANSFORM_DEFINE_COORDINATE(x, mz, y);
NGS_TRANSFORM_DEFINE_COORDINATE(x, mz, my);

NGS_TRANSFORM_DEFINE_COORDINATE(mx, y, z);
NGS_TRANSFORM_DEFINE_COORDINATE(mx, y, mz);
NGS_TRANSFORM_DEFINE_COORDINATE(mx, my, z);
NGS_TRANSFORM_DEFINE_COORDINATE(mx, my, mz);
NGS_TRANSFORM_DEFINE_COORDINATE(mx, z, y);
NGS_TRANSFORM_DEFINE_COORDINATE(mx, z, my);
NGS_TRANSFORM_DEFINE_COORDINATE(mx, mz, y);
NGS_TRANSFORM_DEFINE_COORDINATE(mx, mz, my);

NGS_TRANSFORM_DEFINE_COORDINATE(y, x, z);
NGS_TRANSFORM_DEFINE_COORDINATE(y, x, mz);
NGS_TRANSFORM_DEFINE_COORDINATE(y, mx, z);
NGS_TRANSFORM_DEFINE_COORDINATE(y, mx, mz);
NGS_TRANSFORM_DEFINE_COORDINATE(y, z, x);
NGS_TRANSFORM_DEFINE_COORDINATE(y, z, mx);
NGS_TRANSFORM_DEFINE_COORDINATE(y, mz, x);
NGS_TRANSFORM_DEFINE_COORDINATE(y, mz, mx);

NGS_TRANSFORM_DEFINE_COORDINATE(my, x, z);
NGS_TRANSFORM_DEFINE_COORDINATE(my, x, mz);
NGS_TRANSFORM_DEFINE_COORDINATE(my, mx, z);
NGS_TRANSFORM_DEFINE_COORDINATE(my, mx, mz);
NGS_TRANSFORM_DEFINE_COORDINATE(my, z, x);
NGS_TRANSFORM_DEFINE_COORDINATE(my, z, mx);
NGS_TRANSFORM_DEFINE_COORDINATE(my, mz, x);
NGS_TRANSFORM_DEFINE_COORDINATE(my, mz, mx);

NGS_TRANSFORM_DEFINE_COORDINATE(z, x, y);
NGS_TRANSFORM_DEFINE_COORDINATE(z, x, my);
NGS_TRANSFORM_DEFINE_COORDINATE(z, mx, y);
NGS_TRANSFORM_DEFINE_COORDINATE(z, mx, my);
NGS_TRANSFORM_DEFINE_COORDINATE(z, y, x);
NGS_TRANSFORM_DEFINE_COORDINATE(z, y, mx);
NGS_TRANSFORM_DEFINE_COORDINATE(z, my, x);
NGS_TRANSFORM_DEFINE_COORDINATE(z, my, mx);

NGS_TRANSFORM_DEFINE_COORDINATE(mz, x, y);
NGS_TRANSFORM_DEFINE_COORDINATE(mz, x, my);
NGS_TRANSFORM_DEFINE_COORDINATE(mz, mx, y);
NGS_TRANSFORM_DEFINE_COORDINATE(mz, mx, my);
NGS_TRANSFORM_DEFINE_COORDINATE(mz, y, x);
NGS_TRANSFORM_DEFINE_COORDINATE(mz, y, mx);
NGS_TRANSFORM_DEFINE_COORDINATE(mz, my, x);
NGS_TRANSFORM_DEFINE_COORDINATE(mz, my, mx);

#undef NGS_TRANSFORM_DEFINE_COORDINATE

}
}

template<class _Tag>
inline constexpr bool _is_coordinate = requires{
	{ _Tag::front_type::value } -> mla::CVectorDimensionEqual<3>;
	{ _Tag::right_type::value } -> mla::CVectorDimensionEqual<3>;
	{ _Tag::up_type::value } -> mla::CVectorDimensionEqual<3>;

		requires mla::modulus_squared(_Tag::front_type::value) == 1;
		requires mla::modulus_squared(_Tag::right_type::value) == 1;
		requires mla::modulus_squared(_Tag::up_type::value) == 1;
};

template<class _Tag>
concept CCoordinate = _is_coordinate<std::remove_cvref_t<_Tag>>;

NGS_CCPT_VERIFY(CCoordinate, tag::coordinates::coordinate_x_y_z_f);

NGS_TRANSFORM_END
