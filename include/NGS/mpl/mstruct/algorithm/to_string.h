#pragma once

#include "../basic.h"
#include "../storage.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr ::std::string to_string(const storages::storage_structure auto& s) {
	::std::string str{};
	str += "{";
	str += [&s]<size_t... Index>(::std::index_sequence<Index...>) {
		::std::string str{};
		((str += (Index == 0 ? "" : ", ") + to_strings::to_string(storages::get<Index>(s))), ...);
		return str;
	}(::std::make_index_sequence<basic::field_count_v<decltype(s)>>{});
	str += "}";
	return str;
}

NGS_LIB_MODULE_END