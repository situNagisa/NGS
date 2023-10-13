#pragma once

#include "./variable.h"

NGS_META_STRUCT_TYPE_BEGIN

template<CVariable _Variable>
struct variable_traits {
	constexpr static bool is_reference = std::is_reference_v<typename _Variable::original_type>;
	constexpr static bool is_rvalue_reference = std::is_rvalue_reference_v<typename _Variable::original_type>;
	constexpr static bool is_lvalue_reference = std::is_lvalue_reference_v<typename _Variable::original_type>;
	constexpr static bool is_const = std::is_const_v<typename _Variable::original_type>;
	constexpr static bool is_array = std::is_bounded_array_v<typename _Variable::original_type>;
	constexpr static bool is_range = std::ranges::range<typename _Variable::original_type>;

	constexpr static size_t element_count = [] {
		if constexpr (is_array) {
			return std::extent_v<typename _Variable::original_type, 0>;
		}
		else {
			return 1;
		}
		}();
};

NGS_META_STRUCT_TYPE_END
