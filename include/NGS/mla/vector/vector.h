#pragma once

#include "NGS/mla/vector/container.h"

NGS_MLA_BEGIN

template<size_t _Dim, class _ElementType>
class Vector : public VectorContainer<Vector<_Dim, _ElementType>, std::integral_constant<size_t, _Dim>, _ElementType> {
private:
	using base_type = typename Vector::self_type;
protected:
	using self_type = Vector<_Dim, _ElementType>;
public:
	using element_type = typename base_type::element_type;

	using base_type::base_type;

	using base_type::operator();

	constexpr element_type& operator()(size_t i) { return _data[i]; }
	constexpr const element_type& operator()(size_t i)const { return _data[i]; }

private:
	element_type _data[base_type::dimension];
};
NGS_CCPT_VERIFY(CVectorContainer, Vector<3, int>);

namespace {
constexpr Vector<3, int> _test_vector{1, 2, 3};
static_assert(_test_vector(0) == 1 && _test_vector(1) == 2 && _test_vector(2) == 3, "undefined behavior");
}

template<class _ElementType> using Vector1 = Vector<1, _ElementType>;
template<class _ElementType> using Vector2 = Vector<2, _ElementType>;
template<class _ElementType> using Vector3 = Vector<3, _ElementType>;
template<class _ElementType> using Vector4 = Vector<4, _ElementType>;

using Vector1i = Vector1<int>;
using Vector1f = Vector1<float>;
using Vector1d = Vector1<double>;
using Vector1u = Vector1<unsigned>;
using Vector1s = Vector1<size_t>;

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
using Vector2u = Vector2<unsigned>;
using Vector2s = Vector2<size_t>;

using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;
using Vector3u = Vector3<unsigned>;
using Vector3s = Vector3<size_t>;

using Vector4i = Vector4<int>;
using Vector4f = Vector4<float>;
using Vector4d = Vector4<double>;
using Vector4u = Vector4<unsigned>;
using Vector4s = Vector4<size_t>;

NGS_MLA_END
