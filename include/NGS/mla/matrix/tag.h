#pragma once

#include "NGS/mla/base/tag.h"

NGS_MLA_BEGIN

namespace tag {
struct matrix : unknown {};
struct matrix_container : matrix {};
static_assert(std::derived_from<matrix_container, matrix>);
}


template<class T>
concept CMatrixLayout = requires(size_t index, size_t row_index, size_t col_index, size_t row_count, size_t col_count) {
	{ T::transform(row_index, col_index, row_count, col_count) } -> std::same_as<size_t>;
	{ T::inverse_transform(index, row_count, col_count) } -> std::same_as<std::pair<size_t, size_t>>;
};

namespace tag {


struct row : unknown {
	constexpr static size_t transform(size_t row_index, size_t col_index, size_t /*row_count*/, size_t col_count) {
		return row_index * col_count + col_index;
	}
	constexpr static std::pair<size_t, size_t> inverse_transform(size_t index, size_t /*row_count*/, size_t col_count) {
		return { index / col_count, index % col_count };
	}
};
NGS_CCPT_VERIFY(CMatrixLayout, row);
struct column : unknown {
	constexpr static size_t transform(size_t row_index, size_t col_index, size_t row_count, size_t /*col_count*/) {
		return col_index * row_count + row_index;
	}
	constexpr static std::pair<size_t, size_t> inverse_transform(size_t index, size_t row_count, size_t /*col_count*/) {
		return { index % row_count, index / row_count };
	}
};
NGS_CCPT_VERIFY(CMatrixLayout, column);

}

NGS_MLA_END
