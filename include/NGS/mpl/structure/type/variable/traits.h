#pragma once

#include "./variable.h"

NGS_STRUCTURE_TYPE_BEGIN

template<CVariable _Variable>
struct variable_traits {
	using original_type = typename _Variable::original_type;
	using storage_type = typename _Variable::storage_type;

	constexpr static bool is_reference = std::is_reference_v<original_type>;
	constexpr static bool is_rvalue_reference = std::is_rvalue_reference_v<original_type>;
	constexpr static bool is_lvalue_reference = std::is_lvalue_reference_v<original_type>;
	constexpr static bool is_const = std::is_const_v<original_type>;
	constexpr static bool is_array = std::is_bounded_array_v<original_type>;
	constexpr static bool is_range = std::ranges::range<original_type>;

	using element_type = std::conditional_t<is_array, std::remove_all_extents_t<original_type>, storage_type>;

	constexpr static size_t element_count = [] {
		if constexpr (is_array) {
			return std::extent_v<original_type, 0>;
		}
		else {
			return 1;
		}
		}();
};

NGS_STRUCTURE_TYPE_END
