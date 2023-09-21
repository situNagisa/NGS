#pragma once

#include "NGS/math/mst/defined.h"

NGS_MST_BEGIN

template<class _Type>
concept CSetExprerssion = requires() {
	typename _Type::element_type;
	{ _Type::contains(typename _Type::element_type{}) } -> std::convertible_to<bool>;
		requires CExpression<_Type>;
};

template<class _Expression>
struct SetExpression : Expression<SetExpression<_Expression>> {
	NGS_menvironment(SetExpression);
public:

};

NGS_MST_END
