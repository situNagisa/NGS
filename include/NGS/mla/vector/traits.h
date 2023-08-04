﻿#pragma once

#include "NGS/mla/base/traits.h"
#include "NGS/mla/vector/expression.h"
#include "NGS/mla/vector/tag.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression>
struct vector_traits : type_traits<_Expression> {
private:
	using base_type = typename vector_traits::self_type;
public:
	using self_type = vector_traits<_Expression>;

	using original_type = typename _Expression::expression_type;
	using element_type = typename _Expression::element_type;
	using closure_type = std::conditional_t<std::derived_from<typename original_type::type_category, tag::vector_container>, const original_type&, const original_type>;
	constexpr static size_t dimension = original_type::dimension;
	constexpr static size_t complexity = original_type::complexity;
};

NGS_MLA_END
