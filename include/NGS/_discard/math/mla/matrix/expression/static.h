#pragma once

#include "NGS/math/mla/matrix/expression/expression.h"
#include "NGS/math/mla/vector/expression/static.h"

NGS_MLA_BEGIN

template<size_t _Row, size_t _Col, CScalarExpression _ElementType, _ElementType... _Element>
	requires (_Row* _Col == sizeof...(_Element))
struct NGS_DLL_API StaticMatrix : MatrixExpression<StaticMatrix<_Row, _Col, _ElementType, _Element...>> {
	NGS_MPL_ENVIRON(StaticMatrix);
public:
	using element_type = _ElementType;

	constexpr static size_t row_count = _Row;
	constexpr static size_t col_count = _Col;
	constexpr static size_t element_count = row_count * col_count;
	constexpr static std::array<element_type, element_count> data = { _Element... };

	using base_type::operator();
	constexpr element_type operator()(size_t row_index, size_t col_index)const {
		return data[tag::row::transform(row_index, col_index, row_count, col_count)];
	}
};

template<size_t _Row, size_t _Col, CScalarExpression _ElementType, _ElementType... _Element>
	requires (_Row* _Col == sizeof...(_Element))
using static_matrix_t = StaticMatrix<_Row, _Col, _ElementType, _Element...>;

template<size_t _Row, size_t _Col, CScalarExpression _ElementType, _ElementType... _Element>
	requires (_Row* _Col == sizeof...(_Element))
inline constexpr auto static_matrix_v = static_matrix_t<_Row, _Col, _ElementType, _Element...>();

NGS_CCPT_VERIFY(CMatrixExpression, static_matrix_t<3, 3, int, 1, 2, 3, 4, 5, 6, 7, 8, 9>);

NGS_MLA_END
