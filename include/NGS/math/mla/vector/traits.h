#pragma once

#include "NGS/math/mla/base/traits.h"
#include "NGS/math/mla/vector/expression/concept.h"
#include "NGS/math/mla/vector/tag.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression>
struct NGS_DLL_API vector_traits : type_traits<_Expression> {
private:
	using base_type = typename vector_traits::self_type;
public:
	using self_type = vector_traits;

	using expression_type = std::remove_cvref_t<_Expression>;

	using original_type = typename expression_type::expression_type;
	using element_type = typename expression_type::element_type;
	using closure_type = std::conditional_t<std::derived_from<typename original_type::type_category, tag::vector_container>, const original_type&, const original_type>;
	constexpr static size_t dimension = original_type::dimension;
	constexpr static size_t complexity = original_type::complexity;
};

NGS_MLA_END
