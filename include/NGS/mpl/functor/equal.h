#pragma once

#include "NGS/mpl/defined.h"

NGS_MPL_BEGIN

NGS_mfunction(identically_equal, class _Left, class _Right) {
	NGS_mcst_t result_type = ccpt::bool_<std::same_as<_Left, _Right>>;
};
template<class _Left, class _Right> using identically_equal_t = typename identically_equal<_Left, _Right>::result_type;
template<class _Left, class _Right> constexpr bool identically_equal_v = identically_equal_t<_Left, _Right>::value;

NGS_CCPT_VERIFY2(ccpt::PredicateTest<identically_equal, void, void>);

NGS_mfunction(equal, class _Left, class _Right) {
	NGS_mcst_t result_type = ccpt::bool_<identically_equal_v<std::remove_cvref_t<_Left>,std::remove_cvref_t<_Right>>/* || std::convertible_to<_Left, _Right>&& std::convertible_to<_Right, _Left>*/>;
};
template<class _Left, class _Right> using equal_t = typename equal<_Left, _Right>::result_type;
template<class _Left, class _Right> constexpr bool equal_v = equal_t<_Left, _Right>::value;

NGS_CCPT_VERIFY2(ccpt::PredicateTest<equal, void, void>);

NGS_MPL_END
