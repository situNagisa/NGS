#pragma once

#include "./tag.h"

NGS_MATH_SCALAR_BEGIN

template<class _Type,class _ObjectType = std::remove_reference_t<_Type>>
concept CScalarExpression = yap::CExpression<_ObjectType> && requires(const _ObjectType obj_cst)
{
	requires std::derived_from<typename _ObjectType::expression_category, scalar_expression_tag>;
};

NGS_MATH_SCALAR_END