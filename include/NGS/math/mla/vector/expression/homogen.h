#pragma once

#include "NGS/math/mla/vector/expression/container.h"

NGS_MLA_BEGIN

template<size_t _Dimension, class  _ElementType, class  = std::make_index_sequence<_Dimension - 1>>
	requires (_Dimension > 1)
class NGS_API  HomogenousVector;

template<size_t _Dimension, class  _ElementType, size_t... _Index>
class NGS_API  HomogenousVector<_Dimension, _ElementType, std::index_sequence< _Index...>> : public VectorContainer<HomogenousVector<_Dimension, _ElementType>, std::integral_constant<size_t, _Dimension>, _ElementType> {
	NGS_MPL_ENVIRON(HomogenousVector);
public:
	NGS_MPL_INHERIT_TYPE(element_type, base_type);
	NGS_MPL_INHERIT_TYPE(expression_type, base_type);

	NGS_MPL_INHERIT_VALUE(dimension, base_type);

	constexpr HomogenousVector() = default;
	template<CVectorExpression _Expression>
		requires (dimension == _Expression::expression_type::dimension)
	constexpr HomogenousVector(const _Expression& expression) {
		(((*this)().assign(_Index, expression()(_Index))), ...);
	}
	constexpr HomogenousVector(mpl::sequence_params_t<_Index, element_type>... value) {
		(((*this)().assign(_Index, value)), ...);
	}

	using base_type::operator();
	constexpr element_type operator()(size_t index)const {
		if (index < dimension - 1)
			return _data[index];
		return 1;
	}

	using base_type::assign;
	constexpr expression_type& assign(size_t index, element_type element) {
		_data[index] = element;
		return (*this)();
	}
	constexpr expression_type& assign(size_t index, const CVectorExpression auto& expression) {
		if (index < dimension - 1)
			return _data[index] = expression()(index);
		return (*this)();
	}

private:
	element_type _data[dimension]{};
};
NGS_CCPT_VERIFY(CVectorContainer, HomogenousVector<3, int>);

NGS_MLA_END
