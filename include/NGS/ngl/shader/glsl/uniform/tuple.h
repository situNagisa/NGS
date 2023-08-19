#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/shader/glsl/uniform/location.h"
#include "NGS/ngl/shader/glsl/uniform/functor.h"

NGL_BEGIN

template<class _Tuple>
concept CUniformTuple = requires() {
	{ _Tuple::name };
	{ _Tuple::dimension } -> std::convertible_to<size_t>;
	typename _Tuple::original_type;

		requires mpl::CMetaVariable<_Tuple>;
};

NGS_mfunction(uniform_tuple, static_string _Name, class _Type, size_t _Dimension = 1, size_t _Count = 1) {

	constexpr static auto name = _Name;
	constexpr static size_t dimension = _Dimension;

	using element_type = decltype([] {
		if constexpr (dimension == 1) {
			return declval<_Type>();
		}
		else if constexpr (map::is_matrix_dimension<dimension>) {
			constexpr auto size = map::convert_to_matrix_row_col<dimension>;
			return declval<std::array<_Type,size.x * size.y>>();
		}
		else {
			return declval<std::array<_Type, dimension>>();
		}
		}());
	using original_type = _Type;

	constexpr static size_t element_count = _Count;
	constexpr static size_t element_size = sizeof(element_type);
	constexpr static size_t size = element_count * element_size;
};

template<static_string _Name, class _Type, size_t _Dimension = 1,size_t _Count = 1>
using uniform_ = uniform_tuple<_Name, _Type, _Dimension, _Count>;


NGL_END
