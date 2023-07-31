#pragma  once

#include "NGS/base/base.h"
#include "NGS/math/vector.h"
#include "NGS/math/rectangle.h"
#include "NGS/math/util.h"

#include "NGS/math/BTL.h"

NGS_BEGIN

template<size_t _Row, size_t _Column, CArithmetic _Number, class L = ublas::row_major, class A = ublas::unbounded_array<_Number>>
class Matrix {
public:
	constexpr static size_t row = _Row;
	constexpr static size_t column = _Column;
	using element_type = _Number;
private:
	NGS_DEFINE_TYPE(this, Matrix<row, cloumn, element_type>);
public:


public:
	ublas::matrix<element_type, L, A> matrix_data;
private:
};

NGS_END