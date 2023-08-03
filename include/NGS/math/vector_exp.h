#pragma once

#include "NGS/base/base.h"

#undef _I

namespace std {

	template<size_t _Index, class _Vector>
	constexpr typename _Vector::element_type& get(_Vector&& _Vec);
}

NGS_BEGIN

template<class _Dim, class, class, class = std::make_index_sequence<_Dim::value>>
class BasicVector;

template<
	class _Dim,
	CArithmetic _ElementType,
	class _Derived,
	size_t... _Index
>class BasicVector<_Dim, _ElementType, _Derived, std::index_sequence<_Index...>> {
public:
	constexpr static size_t dimensional = _Dim::value;
	using element_type = _ElementType;

	template<class T> using promote_type = mpl::promote_t<element_type, T>;
public:
	using base_type = BasicVector<_Dim, _ElementType, _Derived, std::index_sequence<_Index...>>;
private:
	NGS_DEFINE_TYPE(derived, _Derived);
public:
	constexpr BasicVector() = default;

	constexpr derived_ref_cst operator()()const { return static_cast<derived_ref_cst>(*this); }


};

template<CArithmetic _ElementType>
struct Point2D : public BasicVector<std::integral_constant<size_t, 2>, _ElementType, Point2D<_ElementType>> {

};

NGS_END
