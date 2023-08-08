#pragma once

#include "NGS/math/defined.h"
#include "NGS/math/mla/matrix.h"

NGS_MATH_BEGIN

template<size_t _Dimension, mla::CScalarExpression _ElementType, mla::CMatrixLayout _Layout = mla::tag::row, mla::CMatrixLayout _HomogenCategory = mla::tag::row>
struct TransformMatrix : mla::HomogeneousMatrix<_Dimension + 1, _ElementType, _Layout, _HomogenCategory> {
private:
	using base_type = TransformMatrix::self_type;
protected:
	using self_type = TransformMatrix;
public:
	NGS_minherit_t(element_type, base_type);
	NGS_minherit(dimension, base_type);

	using base_type::base_type;
	using base_type::operator();
	constexpr self_type& operator()() { return *this; }
	constexpr const self_type& operator()()const { return *this; }

	constexpr self_type& assign(const mla::CMatrixExpression auto& expression) { base_type::assign(expression); return *this; }
	constexpr self_type& assign(size_t index, element_type element) { base_type::assign(index, element); return *this; }
	constexpr self_type& assign(size_t row_index, size_t col_index, element_type element) { base_type::assign(row_index, col_index, element); return *this; }
	constexpr self_type& assign(size_t row_index, size_t col_index, const mla::CMatrixExpression auto& expression) { base_type::assign(row_index, col_index, expression); return *this; }

	template<mla::CVectorExpression _Expression>
		requires requires(self_type self, _Expression offset) { {mla::translate_assign(self, offset)} -> std::convertible_to<self_type&>; }
	constexpr self_type& Translate(const _Expression& offset) { return mla::translate_assign(*this, offset); }
	template<mla::CVectorExpression _Expression>
		requires requires(self_type self, _Expression scale) { {mla::scale_assign(self, scale)} -> std::convertible_to<self_type&>; }
	constexpr self_type& Scale(const _Expression& scale) { return mla::scale_assign(*this, scale); }
	
};

//NGS_CCPT_VERIFY(mla::CHomogeneousMatrix, TransformMatrix<2, int>);
//NGS_CCPT_VERIFY(mla::CMatrixContainer, TransformMatrix<2, int>);

NGS_MATH_END
