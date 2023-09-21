#pragma once

#include "NGS/transform/defined.h"

NGS_TRANSFORM_BEGIN

namespace tag {

template<mla::CScalarExpression _ElementType, _ElementType _Sign, size_t _Index>
struct axis {
	using element_type = _ElementType;
	using value_type = mla::Vector3<element_type>;
	static constexpr auto sign = _Sign;
	static constexpr size_t index = _Index;
	static constexpr value_type value = [] {
		value_type result{};
		result(index) = sign;
		return result;
		}();
};

inline namespace axes {

template<mla::CScalarExpression _ElementType> struct  x : axis<_ElementType, 1, 0> {};
template<mla::CScalarExpression _ElementType> struct mx : axis<_ElementType,-1, 0> {};
template<mla::CScalarExpression _ElementType> struct  y : axis<_ElementType, 1, 1> {};
template<mla::CScalarExpression _ElementType> struct my : axis<_ElementType,-1, 1> {};
template<mla::CScalarExpression _ElementType> struct  z : axis<_ElementType, 1, 2> {};
template<mla::CScalarExpression _ElementType> struct mz : axis<_ElementType,-1, 2> {};

using x_i = x<int>;
using x_f = x<float>;
using x_d = x<double>;
using mx_i = mx<int>;
using mx_f = mx<float>;
using mx_d = mx<double>;

using y_i = y<int>;
using y_f = y<float>;
using y_d = y<double>;
using my_i = my<int>;
using my_f = my<float>;
using my_d = my<double>;

using z_i = z<int>;
using z_f = z<float>;
using z_d = z<double>;
using mz_i = mz<int>;
using mz_f = mz<float>;
using mz_d = mz<double>;

}

}

template<class _Tag>
inline constexpr bool _is_axis = requires{
	{ _Tag::index } -> std::convertible_to<size_t>;
	{ _Tag::sign };
	{ _Tag::value } -> mla::CVectorDimensionEqual<3>;
		requires mla::CScalarExpression<typename _Tag::element_type>;
		requires static_cast<typename _Tag::element_type>(-1) < static_cast<typename _Tag::element_type>(0);
};
template<class _Tag>
concept CAxis = ccpt::Constant<std::remove_cvref_t<_Tag>> && _is_axis<std::remove_cvref_t<_Tag>>;

template<CAxis _Tag, size_t _Index>
inline constexpr bool _axis_is = _Tag::index == _Index;

template<class _Tag> concept CAxisX = CAxis<_Tag> && _axis_is<std::remove_cvref_t<_Tag>, 0>;
template<class _Tag> concept CAxisY = CAxis<_Tag> && _axis_is<std::remove_cvref_t<_Tag>, 1>;
template<class _Tag> concept CAxisZ = CAxis<_Tag> && _axis_is<std::remove_cvref_t<_Tag>, 2>;

NGS_CCPT_VERIFY(CAxis, tag::x_f);
NGS_CCPT_VERIFY(CAxisX, tag::x_f);
NGS_CCPT_VERIFY(CAxisX, tag::x_i);
NGS_CCPT_VERIFY(CAxisX, tag::x_d);
NGS_CCPT_VERIFY(CAxisY, tag::y_d);
NGS_CCPT_VERIFY(CAxisZ, tag::z_d);

NGS_TRANSFORM_END
