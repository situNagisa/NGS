//==========================================================================================================
// @file	:	NGS/NGS_STL
// @CLR		:	4.0.30319.42000
// @author	:	NAGISA
// @data	:	2023/4/7 16:13:20
// @brief	:	
//==========================================================================================================
#pragma  once

#include "NGS/base/version.h"

#include <type_traits>
#include <typeinfo>

#include <memory>

#include <vector>
#include <array>
#include <map>
#include <list>
#include <queue>
#include <unordered_set>
#include <set>
#include <variant>
#include <stack>
#include <span>

#include <functional>

#include <iostream>
#include <fstream>
#include <strstream>
#include <filesystem>

#include <bit>
#include <bitset>

#include <cassert>
#include <cstring>
#include <cmath>
#include <cstdarg>

#include <algorithm>
#include <numbers>
#include <random>

#include <charconv>
#include <chrono>

#include <thread>

#include <ranges>
#include <iterator>
#include <regex>

#include <mutex>


#ifdef NGS_HAS_CPP_20
#include <source_location>
#else
#include <experimental/source_location>
#endif // NGS_CPP_20

//#include <format>

namespace std {
template<typename T>
struct hash<unordered_set<T>> {
	size_t operator()(const unordered_set<T>& s) const {
		size_t seed = s.size();
		for (const auto& i : s)
			seed ^= hash<T>()(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		return seed;
	}
};

/*template<class _Element, ranges::range _Rng>
	requires requires(basic_ostream<_Element> os, ranges::range_value_t<_Rng> v) { os << v; }
inline basic_ostream<_Element>& operator<<(basic_ostream<_Element>& os, _Rng&& container) {
	os << "{";
	for (auto&& i : container)
		os << i << ",";
	os << "}";
	return os;
}*/
}