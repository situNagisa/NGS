#pragma once

#include "NGS/math/mla/vector/expression/container.h"

NGS_MLA_BEGIN

NGS_MLA_CONCEPT_WITH_DEFINE_DEFAULT_EXT(CStandardVector, is_standard_vector,
	CVectorContainerSize,
	requires(const _Type vector_cst,_Type vector) {
		{ vector_cst.data() } -> std::convertible_to<const typename _Type::element_type*>;
		{ vector.data() } -> std::convertible_to<typename _Type::element_type*>;
});

template<size_t _Dimension, class  _ElementType, class  = std::make_index_sequence<_Dimension>>
class NGS_DLL_API  Vector;

template<size_t _Dimension, class  _ElementType, size_t... _Index>
class NGS_DLL_API  Vector<_Dimension, _ElementType, std::index_sequence< _Index...>> : public VectorContainer<Vector<_Dimension, _ElementType>, std::integral_constant<size_t, _Dimension>, _ElementType> {
	NGS_MPL_ENVIRON(Vector);
public:
	NGS_MPL_INHERIT_TYPE(element_type, base_type);
	NGS_MPL_INHERIT_TYPE(expression_type, base_type);

	NGS_MPL_INHERIT_VALUE(dimension, base_type);

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

	constexpr element_type& operator()(size_t i) { return source[i]; }
	constexpr const element_type& operator()(size_t i)const { return source[i]; }

	using base_type::assign;
	constexpr expression_type& assign(size_t index, element_type element) {
		source[index] = element;
		return (*this)();
	}

	constexpr element_type* data(){ return source; }
	constexpr const element_type* data()const{ return source; }

public:
	element_type source[base_type::dimension]{};
};

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

NGS_CCPT_VERIFY(CStandardVector, Vector1i);
NGS_CCPT_VERIFY(CStandardVector, Vector2f);
NGS_CCPT_VERIFY(CStandardVector, Vector3d);
NGS_CCPT_VERIFY(CStandardVector, Vector4s);

NGS_MLA_END
