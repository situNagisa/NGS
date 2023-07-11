#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/STL.h"
#include "NGS/base/type_trait.h"
#include "NGS/base/concepts.h"

NGS_BEGIN

template<_NGS_CPT CArithmetic number1, _NGS_CPT CArithmetic number2>
using CompleteArithmetic = std::conditional_t<
	(sizeof(number1) >= sizeof(number2)),
	std::conditional_t <
	(sizeof(number1) != sizeof(number2)),
	number1,
	std::conditional_t <
	_NGS_CPT CFloatingPoint<number1>,
	number1,
	std::conditional_t<
	_NGS_CPT CUnsignedIntegral<number1>,
	number1,
	number2
	>
	>
	>
	, number2
>;

NGS_END