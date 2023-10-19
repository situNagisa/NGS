#pragma once

#include "NGS/math/mla/matrix/expression/container.h"
#include "NGS/math/mla/scalar/expression/concept.h"
#include "NGS/math/mla/matrix/expression/square.h"

NGS_MLA_BEGIN

NGS_MLA_CONCEPT_WITH_DEFINE_DEFAULT_EXT(CHomogeneousMatrix,is_homogeneous_matrix,
	CMatrixSquare,
	requires{
	true;
	//typename _Type::homogen_category;
	//{ _Type::dimension } -> std::convertible_to<size_t>;
});

template<size_t _Dimension, CScalarExpression _ElementType, CMatrixLayout _Layout = tag::row, class = std::make_index_sequence<_Dimension* (_Dimension - 1)>>
struct NGS_API HomogeneousMatrix;

template<size_t _Dimension, CScalarExpression _ElementType, CMatrixLayout _Layout,size_t... _Index>
	requires (_Dimension > 1)
struct NGS_API HomogeneousMatrix<
	_Dimension,
	_ElementType, _Layout,
	std::index_sequence<_Index...>> :
	MatrixContainer<
	HomogeneousMatrix<
	_Dimension, _ElementType, _Layout>,
	std::integral_constant<size_t, _Dimension>, std::integral_constant<size_t, _Dimension>,
	_ElementType, _Layout> {
	NGS_MPL_ENVIRON(HomogeneousMatrix);
public:
	NGS_MPL_INHERIT_TYPE(expression_type, base_type);
	NGS_MPL_INHERIT_TYPE(element_type, base_type);
	NGS_MPL_INHERIT_TYPE(layout_category, base_type);

	NGS_MPL_INHERIT_VALUE(row_count, base_type);
	NGS_MPL_INHERIT_VALUE(col_count, base_type);
	NGS_MPL_INHERIT_VALUE(element_count, base_type);

	constexpr static size_t dimension = _Dimension;

	constexpr HomogeneousMatrix() = default;
	constexpr HomogeneousMatrix(mpl::sequence_params_t<_Index, element_type>... value) {
		std::array<element_type, element_count> values{ value... };
		size_t index = 0;
		for (size_t row_index = 0; row_index < row_count - 1 && index < sizeof...(value); row_index++)
		{
			for (size_t col_index = 0; col_index < col_count && index < sizeof...(value); col_index++)
			{
				(*this)().assign(row_index, col_index, values[index]);
				index++;
			}
		}
	}
	template<CMatrixExpression _Expression>
		requires is_similar<expression_type, _Expression> || (_Expression::col_count == dimension && _Expression::row_count == dimension - 1)
		constexpr HomogeneousMatrix(const _Expression & expression) {
		for (size_t row_index = 0; row_index < row_count - 1; row_index++)
		{
			for (size_t col_index = 0; col_index < col_count; col_index++)
			{
				assign(row_index, col_index, expression);
			}
		}
	}

	using base_type::operator();
	constexpr element_type operator()(size_t index)const {
		return _data[index];
	}
	constexpr element_type operator()(size_t row_index, size_t col_index)const {
		if (row_index != row_count - 1)
			return _data[layout_category::transform(row_index, col_index, dimension - 1, dimension)];
		return col_index == col_count - 1;
	}
	using base_type::assign;
	constexpr expression_type& assign(size_t index, element_type element) {
		if (index < dimension * (dimension - 1))
			_data[index] = element;
		return (*this)();
	}
	constexpr expression_type& assign(size_t row_index, size_t col_index, element_type element) {
		if (row_index != row_count - 1)
			_data[layout_category::transform(row_index, col_index, dimension - 1, dimension)] = element;
		return (*this)();
	}
	constexpr expression_type& assign(size_t row_index, size_t col_index, const CMatrixExpression auto& expression) {
		if (row_index != row_count - 1)
			_data[layout_category::transform(row_index, col_index, dimension - 1, dimension)] = static_cast<element_type>(expression()(row_index, col_index));
		return (*this)();
	}
private:
	element_type _data[dimension * (dimension - 1)]{};
};
NGS_CCPT_VERIFY(CMatrixContainer, HomogeneousMatrix<3, int>);

NGS_MLA_END
