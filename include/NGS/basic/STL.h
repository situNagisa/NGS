//==========================================================================================================
// @file	:	NGS/NGS_STL
// @CLR		:	4.0.30319.42000
// @author	:	NAGISA
// @data	:	2023/4/7 16:13:20
// @brief	:	
//==========================================================================================================
#pragma  once

//cpp library header
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

//cpp 11 header
#include <array>
#include <atomic>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>

//cpp 14 header
#include <shared_mutex>

//cpp 17 header
#include <any>
#include <charconv>
#include <execution>
#include <filesystem>
#include <memory_resource>
#include <optional>
#include <string_view>
#include <variant>

//cpp 20 header
#ifdef __has_include

#if __has_include(<barrier>)
#   include <barrier>
#endif

#if __has_include(<bit>)
#	include <bit>
#endif

#if __has_include(<compare>)
#	include <compare>
#endif

#if __has_include(<concepts>)
#	include <concepts>
#endif

#if __has_include(<coroutine>)
#	include <coroutine>
#endif

#if __has_include(<format>)
#	include <format>
#endif

#if __has_include(<latch>)
#	include <latch>
#endif

#if __has_include(<numbers>)
#	include <numbers>
#endif

#if __has_include(<ranges>)
#	include <ranges>
#endif

#if __has_include(<semaphore>)
#	include <semaphore>
#endif 

#if __has_include(<source_location>)
#	include <source_location>
#elif __has_include(<experimental/source_location>)
#	include <experimental/source_location>
#endif

#if __has_include(<span>)
#	include <span>
#endif

#if __has_include(<stop_token>)
#	include <stop_token>
#endif

#if __has_include(<syncstream>)
#	include <syncstream>
#endif

#if __has_include(<version>)
#	include <version>
#endif

#endif

//cpp 23 header
#ifdef __has_include

#if __has_include(<expected>)
#	include <expected>
#endif

#if __has_include(<flat_map>)
#	include <flat_map>
#endif

#if __has_include(<flat_set>)
#	include <flat_set>
#endif

#if __has_include(<generator>)
#	include <generator>
#endif

#if __has_include(<mdspan>)
#	include <mdspan>
#endif

#if __has_include(<print>)
#	include <print>
#endif

#if __has_include(<spanstream>)
#	include <spanstream>
#endif

#if __has_include(<stacktrace>)
#	include <stacktrace>
#endif

#if __has_include(<stdfloat>)
#	include <stdfloat>
#endif

#endif

//cpp 26 header
#ifdef __has_include

#if __has_include(<debugging>)
#	include <debugging>
#endif

#if __has_include(<hazard_pointer>)
#	include <hazard_pointer>
#endif

#if __has_include(<inplace_vector>)
#	include <inplace_vector>
#endif

#if __has_include(<linalg>)
#	include <linalg>
#endif

#if __has_include(<rcu>)
#	include <rcu>
#endif

#if __has_include(<text_encoding>)
#	include <text_encoding>
#endif

#endif