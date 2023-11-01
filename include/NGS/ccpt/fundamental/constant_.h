#pragma once

#include "../defined.h"

NGS_CCPT_BEGIN

template<class  T = void>
concept constant = requires() {
	typename T::value_type;
	{ T::value } -> std::convertible_to<typename T::value_type>;
};

template<class  _Type, _Type _Value>
struct NGS_DLL_API constant_ {
	using value_type = _Type;
	static constexpr value_type value = _Value;
};

NGS_CCPT_END
