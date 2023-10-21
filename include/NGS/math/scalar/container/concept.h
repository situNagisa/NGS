#pragma once

#include "../expression/concept.h"
#include "./tag.h"

NGS_MATH_SCALAR_BEGIN

template<class _Type, class _ObjectType = std::remove_reference_t<_Type>>
concept CScalarContainer = CScalarExpression<_ObjectType> && requires(_ObjectType obj)
{
	requires std::derived_from<typename _ObjectType::expression_category, scalar_container_tag>;
};

NGS_MATH_SCALAR_END