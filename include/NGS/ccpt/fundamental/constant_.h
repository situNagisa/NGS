#pragma once

#include "../defined.h"

NGS_CCPT_BEGIN

namespace detail
{
	template<class _T, class _V>
	constexpr bool is_constant()
	{
		if constexpr (::std::same_as<_V, void>)
		{
			return requires{
				typename _T::value_type;
				{ _T::value } -> std::convertible_to<typename _T::value_type>;
			};
		}
		else
		{
			return requires{
				{ _T::value } -> std::convertible_to<typename _T::value_type>;
				requires ::std::same_as<typename _T::value_type, _V>;
			};
		}
	}
}

template<class _T = void, class _ValueType = void>
concept constant = detail::is_constant<_T, _ValueType>();

template<class  _Type, _Type _Value>
struct NGS_DLL_API constant_ {
	using value_type = _Type;
	static constexpr value_type value = _Value;
};

NGS_CCPT_END
