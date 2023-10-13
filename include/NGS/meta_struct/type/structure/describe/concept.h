#pragma once

#include "NGS/meta_struct/type/variable/concept.h"

NGS_META_STRUCT_TYPE_BEGIN

template<class _Structure = void>
concept CStructureDescribe = requires() {
	{ _Structure::variable_count } -> std::convertible_to<size_t>;
	{ _Structure::size } -> std::convertible_to<size_t>;
	{ _Structure::align } -> std::convertible_to<size_t>;
	{ _Structure::GET_VARIABLES() };

		requires (_Structure::variable_count > 0 && CVariable<typename _Structure::template variable_at<0>>);
		requires mpl::CVector<typename _Structure::variable_types>;
};

NGS_META_STRUCT_TYPE_END
