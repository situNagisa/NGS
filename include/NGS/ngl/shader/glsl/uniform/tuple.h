#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/shader/glsl/uniform/location.h"
#include "NGS/ngl/shader/glsl/uniform/functor.h"

NGL_BEGIN
/*
template<class _Tuple>
concept CUniformTuple = mpl::CMetaVariable<_Tuple> && requires() {
	{ _Tuple::name };
};

NGS_MPL_FUNCTION(uniform_tuple, static_strings::static_string _Name, class _Type, size_t _Count = 1) {
	static_assert(mla::CStandardMatrix<_Type> || mla::CStandardVector<_Type> || mla::CScalarExpression<_Type>, "the type must be a scalar, vector or matrix");

	using element_type = _Type;

	constexpr static auto name = _Name;

	constexpr static size_t element_count = _Count;
	constexpr static size_t element_size = sizeof(element_type);
	constexpr static size_t size = element_count * element_size;
};

template<static_strings::static_string _Name, class _Type, size_t _Count = 1>
using uniform_ = uniform_tuple<_Name, _Type, _Count>;
*/

NGL_END
