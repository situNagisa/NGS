#pragma once

#include "./concept.h"

NGS_YAP_BEGIN

template<ccpt::CRPT _Expression>
struct NGS_API expression {
protected:
	using self_type = expression;
public:
	constexpr static size_t complexity = 0;
	using expression_type = _Expression;
	using type_category = void;

	constexpr expression() = default;

	const self_type& operator=(const self_type&) = delete;

	constexpr expression_type& operator()() { return static_cast<expression_type&>(*this); }
	constexpr const expression_type& operator()()const { return static_cast<const expression_type&>(*this); }
};

NGS_YAP_END
