#pragma once

#include "NGS/math/mla/scalar/expression/concept.h"
#include "NGS/math/mla/vector/expression/concept.h"
#include "NGS/math/mla/matrix/expression/concept.h"

#include "NGS/math/mla/matrix/traits.h"
#include "NGS/math/mla/vector/traits.h"

NGS_MLA_BEGIN

template<class _Left,class _Right>
struct is_multiplicative {
	using left_type = std::remove_cvref_t<_Left>;
	using right_type = std::remove_cvref_t<_Right>;

	using value_type = bool;
	static constexpr value_type value = [] {
		//matrix - scalar
		if constexpr (CMatrixExpression<left_type> && CScalarExpression<right_type>) {
			return true;
		}
		else if constexpr (CScalarExpression<left_type> && CMatrixExpression<right_type> ) {
			return true;
		}
		//vector - scalar
		else if constexpr (CVectorExpression<left_type> && CScalarExpression<right_type>) {
			return true;
		}
		else if constexpr (CScalarExpression<left_type> && CVectorExpression<right_type>) {
			return true;
		}
		//matrix - vector
		else if constexpr (CMatrixExpression<left_type> && CVectorExpression<right_type>) {
			return left_type::col_count == right_type::dimension;
		}
		else if constexpr (CVectorExpression<left_type> && CMatrixExpression<right_type>) {
			return left_type::dimension == right_type::row_count;
		}
		//matrix - matrix
		else if constexpr (CMatrixExpression<left_type> && CMatrixExpression<right_type>) {
			return left_type::col_count == right_type::row_count;
		}
		else return false;
		
		}();
};

template<class _Left,class _Right>
constexpr bool is_multiplicative_v = is_multiplicative<_Left,_Right>::value;

template<class _Left,class _Right>
concept CMultiplicative = is_multiplicative_v<_Left,_Right>;

NGS_MLA_END
