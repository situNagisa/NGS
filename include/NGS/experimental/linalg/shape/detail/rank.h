#pragma once

#include "./extent.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using rank_t = ::std::size_t;

template<class T>
concept ranks =
	::std::ranges::sized_range<T>
	&& ::std::ranges::input_range<T>
	&& ::std::same_as<::std::remove_cvref_t<::std::ranges::range_value_t<T>>, extent>
;

constexpr rank_t rank(ranks auto&& r)
{
	return ::std::ranges::size(NGS_PP_PERFECT_FORWARD(r));
}

constexpr rank_t rank_dynamic(ranks auto&& r)
{
	return ::std::ranges::count_if(NGS_PP_PERFECT_FORWARD(r), extent::is_dynamic);
}

constexpr auto static_extent(ranks auto&& r, rank_t i)
{
	return *::std::ranges::next(::std::ranges::begin(NGS_PP_PERFECT_FORWARD(r)), i);
}

constexpr auto dynamic_index(const ranks auto& r, rank_t i)
{
	NGS_ASSERT_IF_CONSTEVAL(i <= NGS_LIB_MODULE_NAME::rank(r));
	return ::std::ranges::count_if(r | ::std::views::take(i), extent::is_dynamic);
}

constexpr auto dynamic_index_inv(const ranks auto& r, rank_t i)
{
	NGS_ASSERT_IF_CONSTEVAL(i <= NGS_LIB_MODULE_NAME::rank_dynamic(r));
	rank_t j = 0;
	while (NGS_LIB_MODULE_NAME::dynamic_index(r, j + 1) != i + 1)
	{
		j++;
	}
	return j;
}

constexpr auto dynamic_indices(ranks auto&& r)
{
	::std::array<rank_t, NGS_LIB_MODULE_NAME::rank(r)> result{};
	rank_t counter = 0;
	for (rank_t index = 0; index < NGS_LIB_MODULE_NAME::rank(r); ++index) {
		result[index] = counter;
		if (NGS_LIB_MODULE_NAME::static_extent(r, index).is_dynamic()) {
			++counter;
		}
	}
	result[NGS_LIB_MODULE_NAME::rank(r)] = counter;
	return result;
}
constexpr auto dynamic_indices_inv(ranks auto&& r)
{
	::std::array<rank_t, NGS_LIB_MODULE_NAME::rank_dynamic(r)> result{};
	rank_t counter = 0;
	for (rank_t index = 0; index < NGS_LIB_MODULE_NAME::rank(r); ++index) {
		if (NGS_LIB_MODULE_NAME::static_extent(r, index).is_dynamic()) {
			result[counter] = index;
			++counter;
		}
	}
	return result;
}

constexpr auto dynamic_equal(const ranks auto& left, const ranks auto& right)
{
	return ::std::ranges::all_of(::std::views::zip(left, right), [](auto element)
		{
			auto&& [l, r] = element;
			return NGS_LIB_MODULE_NAME::dynamic_equal(l, r);
		});
}

constexpr auto is_dynamic_assign(const ranks auto& left, const ranks auto& right)
{
	return ::std::ranges::any_of(::std::views::zip(left, right), [](auto element)
		{
			auto&& [l, r] = element;
			return !l.is_dynamic() && r.is_dynamic();
		});
}

NGS_LIB_MODULE_END