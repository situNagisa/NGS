#pragma once

#include "NGS/math/mla/vector/expression/expression.h"

NGS_MLA_BEGIN

template<CTemplateFrom<std::basic_ostream> _Ostream, CVectorExpression _Expression>
_Ostream& operator<<(_Ostream& os, const _Expression& expr) {
	os << "(";
	for (auto it = std::ranges::begin(expr); it != std::ranges::end(expr); it++)
	{
		os << *it << ((it != std::ranges::end(expr) - 1) ? ", " : "");
	}

	os << ")";
	return os;
}

NGS_MLA_END
