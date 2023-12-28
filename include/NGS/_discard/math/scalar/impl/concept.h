#pragma once

#include "../container.h"

NGS_MATH_SCALAR_BEGIN

template<class _Type, class _ObjectType = std::remove_reference_t<_Type>>
concept CScalar = CScalarContainer<_ObjectType> && requires(_ObjectType obj, const _ObjectType obj_cst)
{
	true;
};

NGS_MATH_SCALAR_END