#pragma once

#include "NGS/math/mla/vector/expression/container.h"

NGS_MLA_BEGIN

template<size_t _Dimension, class  _ElementType, class  = std::make_index_sequence<_Dimension>>
class NGS_API  Vector;

template<size_t _Dimension, class  _ElementType, size_t... _Index>
class NGS_API  Vector<_Dimension, _ElementType, std::index_sequence< _Index...>> : public VectorContainer<Vector<_Dimension, _ElementType>, std::integral_constant<size_t, _Dimension>, _ElementType> {
private:
	using base_type = typename Vector::self_type;
protected:
	using self_type = Vector;
public:
	NGS_minherit_t(element_type, base_type);
	NGS_minherit_t(expression_type, base_type);

	NGS_minherit(dimension, base_type);

	constexpr Vector() = default;
	template<CVectorExpression _Expression>
		requires (dimension == _Expression::expression_type::dimension)
	constexpr Vector(const _Expression& expression) {
		(((*this)().assign(_Index, expression)), ...);
	}
	constexpr Vector(mpl::sequence_params_t<_Index, element_type>... value) {
		(((*this)().assign(_Index, value)), ...);
	}

	using base_type::operator();

	constexpr element_type& operator()(size_t i) { return _data[i]; }
	constexpr const element_type& operator()(size_t i)const { return _data[i]; }

	using base_type::assign;
	constexpr expression_type& assign(size_t index, element_type element) {
		_data[index] = element;
		return (*this)();
	}

private:
	element_type _data[base_type::dimension]{};
};
NGS_CCPT_VERIFY(CVectorContainer, Vector<3, int>);

namespace {
constexpr Vector<3, int> _test_vector{1, 2, 3};
static_assert(_test_vector(0) == 1 && _test_vector(1) == 2 && _test_vector(2) == 3, "undefined behavior");
}

template<class  _ElementType> using Vector1 = Vector<1, _ElementType>;
template<class  _ElementType> using Vector2 = Vector<2, _ElementType>;
template<class  _ElementType> using Vector3 = Vector<3, _ElementType>;
template<class  _ElementType> using Vector4 = Vector<4, _ElementType>;

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
