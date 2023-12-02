#pragma once

#include "NGS/base/defined.h"

NGS_BEGIN

template<class  T, class  U>
auto as(U&& object) {
	if constexpr (std::is_pointer_v<std::remove_reference_t<U>>) {
		using out_type = std::conditional_t<std::is_const_v<std::remove_pointer_t<std::remove_reference_t<U>>>, const T*, T*>;
		return dynamic_cast<out_type>(object);
	}
	else {
		using out_type = std::conditional_t<std::is_const_v<U>, const T*, T*>;
		return dynamic_cast<out_type>(&object);
	}
}

template<class  T>
bool is(auto&& object) { return as<T>(std::forward<T>(object)) != nullptr; }

NGS_END
