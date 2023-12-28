#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

BOOST_AUTO_TEST_CASE(container_vector)
{
	static_assert(contiguous_vector<::std::array<int, 3>>, "vector is not satisfy contiguous_vector");
	static_assert(contiguous_vector<vector3i&>, "vector is not satisfy contiguous_vector");
	static_assert(contiguous_vector<vectori>, "vector is not satisfy contiguous_vector");
	static_assert(output_vector<vector3i>, "vector is not satisfy output_vector");
	static_assert(!output_vector<const vector3i>, "const vector is satisfy output_vector");

	static_assert(contiguous_vector<views::scalar<int>>);
	constexpr vector3i a;
	vectori b(3, 0);
	constexpr views::scalar c(1);
	static_assert(adapter_vector<views::scalar<int>>);

	constexpr auto i0 = is_same_size(a, a);
	constexpr auto i1 = is_same_size(a, c);
	NGS_LOGL(debug, is_same_size(a, b));

	//using iterator_type = view_iterator<int, test_dereference, test_subtract, test_plus_assign, int>;
	using iterator_type = views::add_view<vector3i, vector3i>::iterator;

	static_assert(::std::random_access_iterator<iterator_type>);

	static_assert(::std::ranges::random_access_range<views::add_view<vector3i, vector3i>>);
	static_assert(::std::ranges::random_access_range<views::subtract_view<vector3i, vector3i>>);
	static_assert(::std::ranges::random_access_range<views::multiply_view<vector3i, vector3i>>);
	static_assert(::std::ranges::random_access_range<views::divide_view<vector3i, vector3i>>);

	constexpr vector3i result = vector3i(10, 0, 0) + vector3i();

	constexpr auto normal = views::normalize(result);
	constexpr vector3i negative = -normal;

	::std::cout << ::ngs::to_string(negative) << ::std::endl;
}

NGS_LIB_END