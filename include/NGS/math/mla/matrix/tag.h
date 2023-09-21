#pragma once

#include "NGS/math/mla/base/tag.h"

NGS_MLA_BEGIN

namespace tag {
struct NGS_API matrix : unknown {};
struct NGS_API matrix_container : matrix {};
static_assert(std::derived_from<matrix_container, matrix>);
}


NGS_MLA_CONCEPT_WITH_DEFINE_DEFAULT(CMatrixLayout,is_matrix_layout,
	requires(size_t index, size_t row_index, size_t col_index, size_t row_count, size_t col_count) {
	{ _Type::transform(row_index, col_index, row_count, col_count) } -> std::same_as<size_t>;
	{ _Type::inverse_transform(index, row_count, col_count) } -> std::same_as<std::pair<size_t, size_t>>;
});

namespace tag {


struct NGS_API row : unknown {
	constexpr static size_t transform(size_t row_index, size_t col_index, size_t /*row_count*/, size_t col_count) {
		return row_index * col_count + col_index;
	}
	constexpr static std::pair<size_t, size_t> inverse_transform(size_t index, size_t /*row_count*/, size_t col_count) {
		return { index / col_count, index % col_count };
	}
};
NGS_CCPT_VERIFY(CMatrixLayout, row);
struct NGS_API column : unknown {
	constexpr static size_t transform(size_t row_index, size_t col_index, size_t row_count, size_t /*col_count*/) {
		return col_index * row_count + row_index;
	}
	constexpr static std::pair<size_t, size_t> inverse_transform(size_t index, size_t row_count, size_t /*col_count*/) {
		return { index % row_count, index / row_count };
	}
};
NGS_CCPT_VERIFY(CMatrixLayout, column);

}

NGS_MLA_CONCEPT_WITH_DEFINE_DEFAULT(CMatrixTriangularTag,is_matrix_triangular_tag,
	requires(size_t index, size_t row_index, size_t col_index, size_t row_count, size_t col_count) {
	{ _Type::has_element(row_index, col_index, row_count, col_count) } -> std::convertible_to<bool>;
	{ _Type::template has_element<tag::row>(index, row_count, col_count) } -> std::convertible_to<bool>;
	{ _Type::template transform<tag::row>(index, row_count, col_count) } -> std::convertible_to<size_t>;
	{ _Type::template transform<tag::row>(row_index, col_index, row_count, col_count) } -> std::convertible_to<size_t>;
});

namespace tag {

struct NGS_API lower : unknown {
	constexpr static bool has_element(size_t row_index, size_t col_index, size_t row_count, size_t col_count) {
		return row_index >= col_index;
	}
	template<CMatrixLayout _Layout = row>
	constexpr static bool has_element(size_t index, size_t row_count, size_t col_count) {
		auto [row_index, col_index] = _Layout::inverse_transform(index, row_count, col_count);
		return has_element(row_index, col_index, row_count, col_count);
	}

	template<CMatrixLayout _Layout = row>
	constexpr static size_t transform(size_t row_index, size_t col_index, size_t row_count, size_t col_count) {
		if constexpr (std::same_as<_Layout, row>) {
			size_t index = _Layout::transform(row_index, col_index, row_count, col_count);
			return index - ((2 * row_count - row_index - 1) * (row_index) / 2);
		}
		else if constexpr (std::same_as<_Layout, column>) {
			size_t index = _Layout::transform(row_index, col_index, row_count, col_count);
			return index - (col_index * (col_index + 1) / 2);
		}
	}
	template<CMatrixLayout _Layout = row>
	constexpr static size_t transform(size_t index, size_t row_count, size_t col_count) {
		auto [row_index, col_index] = _Layout::inverse_transform(index, row_count, col_count);
		if constexpr (std::same_as<_Layout, row>) {
			return index - ((2 * row_count - row_index - 1) * (row_index) / 2);
		}
		else if constexpr (std::same_as<_Layout, column>) {
			return index - (col_index * (col_index + 1) / 2);
		}
	}
};
NGS_CCPT_VERIFY(CMatrixTriangularTag, lower);

struct NGS_API upper : unknown {
	constexpr static bool has_element(size_t row_index, size_t col_index, size_t row_count, size_t col_count) {
		return row_index <= col_index;
	}
	template<CMatrixLayout _Layout = row>
	constexpr static bool has_element(size_t index, size_t row_count, size_t col_count) {
		auto [row_index, col_index] = _Layout::inverse_transform(index, row_count, col_count);
		return has_element(row_index, col_index, row_count, col_count);
	}

	template<CMatrixLayout _Layout = row>
	constexpr static size_t transform(size_t row_index, size_t col_index, size_t row_count, size_t col_count) {
		if constexpr (std::same_as<_Layout, row>) {
			size_t index = _Layout::transform(row_index, col_index, row_count, col_count);
			return index - (row_index * (row_index + 1) / 2);
		}
		else if constexpr (std::same_as<_Layout, column>) {
			size_t index = _Layout::transform(row_index, col_index, row_count, col_count);
			return index - ((2 * col_count - col_index - 1) * (col_index) / 2);
		}
	}
	template<CMatrixLayout _Layout = row>
	constexpr static size_t transform(size_t index, size_t row_count, size_t col_count) {
		auto [row_index, col_index] = _Layout::inverse_transform(index, row_count, col_count);
		if constexpr (std::same_as<_Layout, row>) {
			return index - (row_index * (row_index + 1) / 2);
		}
		else if constexpr (std::same_as<_Layout, column>) {
			return index - ((2 * col_count - col_index - 1) * (col_index) / 2);
		}
	}

};
NGS_CCPT_VERIFY(CMatrixTriangularTag, upper);


}

NGS_MLA_END
