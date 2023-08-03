#pragma  once

#include "NGS/base/base.h"
#include "NGS/math/vector.h"
#include "NGS/math/rectangle.h"
#include "NGS/math/util.h"

#include "NGS/math/BTL.h"

NGS_BEGIN

template<size_t _Row, size_t _Column, CArithmetic _Number, class L = ublas::row_major, class A = ublas::unbounded_array<_Number>>
class _BasicMatrix {
public:
	constexpr static size_t row = _Row;
	constexpr static size_t column = _Column;
	using element_type = _Number;
protected:
	using base = _BasicMatrix<row, column, element_type, L, A>;
private:
	NGS_DEFINE_TYPE(__this, base);
public:
	auto& operator()(size_t i, size_t j) { return matrix(i, j); }
	const auto& operator()(size_t i, size_t j) const { return matrix(i, j); }

	auto row_size() const { return matrix.size1(); }
	auto column_size() const { return matrix.size2(); }
	auto size() const { return row_size() * column_size(); }

public:
	ublas::matrix<element_type, L, A> matrix{ row,column };
private:
};

template<size_t _Row, size_t _Column, CArithmetic _Number, class L = ublas::row_major, class A = ublas::unbounded_array<_Number>>
class Matrix : public _BasicMatrix<_Row, _Column, _Number, L, A> {};

template<size_t _Length, CArithmetic _Number, class L, class A>
class Matrix<_Length, _Length, _Number, L, A> : public _BasicMatrix<_Length, _Length, _Number, L, A> {
private:
	using base = typename Matrix::base;
	NGS_DEFINE_TYPE(__this, Matrix<base::row, base::column, typename base::element_type, L, A>);
public:

};

void aa() {
	_BasicMatrix<3, 3, float> matrix;

}

NGS_END