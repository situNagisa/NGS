#pragma once

#include "NGS/math/defined.h"
#include "NGS/math/geometry/point.h"

NGS_MATH_BEGIN

NGS_MLA_CONCEPT_WITH_DEFINE_DEFAULT_EXT(CQuaternion,is_quaternion,
	mla::CVectorContainer,
	requires(_Type quaternion,const _Type quaternion_cst) {
	{ quaternion_cst.w } -> std::convertible_to<typename _Type::element_type>;
	{ quaternion_cst.v } -> mla::CVectorContainer;
});

template<class  _ElementType>
struct NGS_API Quaternion : mla::VectorContainer<Quaternion<_ElementType>, ccpt::uint_<4>, _ElementType> {
	NGS_MPL_ENVIRON(Quaternion);
public:
	NGS_MPL_INHERIT_TYPE(element_type, base_type);
	NGS_MPL_INHERIT_TYPE(expression_type, base_type);

	using vector_type = Point3<element_type>;

	using base_type::base_type;
	constexpr Quaternion() = default;
	constexpr Quaternion(
		element_type x,
		element_type y,
		element_type z,
		element_type w
	)
		: v(x, y, z)
		, w(w)
	{}
	constexpr Quaternion(
		const vector_type& v,
		element_type w
	)
		: v(v)
		, w(w)
	{}

	template<mla::CVectorExpression _Expression>
		requires (base_type::dimension <= _Expression::expression_type::dimension)
	constexpr Quaternion(const _Expression& expression)
		: Quaternion(expression()(0), expression()(1), expression()(2),expression()(3))
	{}
	
	using base_type::assign;
	constexpr expression_type& assign(size_t index, element_type element) {
		if (index == 0) v.assign(0, element);
		if (index == 1) v.assign(1, element);
		if (index == 2) v.assign(2, element);
		if (index == 3) w = element;
		return (*this)();
	}

	using base_type::operator();
	constexpr element_type& operator()(size_t i) {
		if (i == 0)return v(0);
		if (i == 1)return v(1);
		if (i == 2)return v(2);
		if (i == 3)return w;
		return w;
	}
	constexpr element_type operator()(size_t i)const { 
		if (i == 0)return v(0);
		if (i == 1)return v(1);
		if (i == 2)return v(2);
		if (i == 3)return w;
		return 0;
	}

	constexpr element_type* data() { return v.data(); }
	constexpr const element_type* data()const { return v.data(); }

	vector_type v{};
	element_type w = 0;
};

NGS_CCPT_VERIFY(CQuaternion, Quaternion<int>);

NGS_MATH_END
