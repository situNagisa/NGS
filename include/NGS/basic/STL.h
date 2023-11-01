//==========================================================================================================
// @file	:	NGS/NGS_STL
// @CLR		:	4.0.30319.42000
// @author	:	NAGISA
// @data	:	2023/4/7 16:13:20
// @brief	:	
//==========================================================================================================
#pragma  once

#include <version>
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
#include <tuple>
#include <valarray>

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

#include <complex>

#ifdef __cpp_lib_source_location
#	include <source_location>
#elif __has_include(<experimental/source_location>)
#	include <experimental / source_location>
#else

#endif

#ifdef __cpp_lib_format
#include <format>
#endif