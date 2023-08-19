#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/shader/glsl/uniform/location.h"

NGL_BEGIN

template<class _Tuple>
concept CUniformTuple = requires() {
	{ _Tuple::name };
	{ _Tuple::dimension } -> std::convertible_to<size_t>;

		requires mpl::CMetaVariable<_Tuple>;
};

NGS_mfunction(uniform_tuple, static_string _Name, class _Type, size_t _Dimension = 1, size_t _Count = 1) {
	using element_type = _Type;

	constexpr static auto name = _Name;
	constexpr static size_t dimension = _Dimension;

	constexpr static size_t element_count = _Count;
	constexpr static size_t element_size = sizeof(element_type);
	constexpr static size_t size = element_count * element_size;
};

template<static_string _Name, class _Type, size_t _Count = 1>
using uniform_ = uniform_tuple<_Name, _Type, _Count>;


NGL_END
