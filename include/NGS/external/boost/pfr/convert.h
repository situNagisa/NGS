#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<class _T, class _U>
constexpr auto convert(_U&& target)
{
	using naked_type = type_traits::naked_t<_U>;
	return[&]<size_t... _Index>(std::index_sequence<_Index...>) {
		_T t{};
		((
			::boost::pfr::get<_Index>(t) = static_cast<::boost::pfr::tuple_element_t<_Index, _T>>(::boost::pfr::get<_Index>(target))
			), ...);
		return t;
	}(std::make_index_sequence<::boost::pfr::tuple_size_v<naked_type>>());
}


NGS_LIB_END