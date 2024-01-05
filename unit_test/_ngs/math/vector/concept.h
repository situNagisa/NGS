#pragma once

#include "./defined.h"


TEST(math_vector, concept) {
	using namespace ::ngs::math;
	using namespace ::ngs::math::vectors;

	{
		struct adapter_range
		{
			constexpr int* begin()const { return nullptr; }
			constexpr adapter_sentinel end() const { return {}; }
		};
		static_assert(::std::ranges::random_access_range<adapter_range>);
		static_assert(::std::ranges::contiguous_range<adapter_range>);
		static_assert(!::std::ranges::sized_range<adapter_range>);
	}
	using static_vector_type = vector3<int>;
	{
		static_assert(contiguous_vector<static_vector_type>);
		static_assert(sized_vector<static_vector_type>);
		static_assert(output_vector<static_vector_type>);
		static_assert(static_extent_vector<static_vector_type>);
	}
	using dynamic_vector_type = vector<int>;
	{
		static_assert(contiguous_vector<dynamic_vector_type>);
		static_assert(sized_vector<dynamic_vector_type>);
		static_assert(output_vector<dynamic_vector_type>);
		static_assert(!static_extent_vector<dynamic_vector_type>);
	}
	using adapter_vector_type = views::trivial_vector<int>;
	{
		static_assert(input_vector<adapter_vector_type>);
		static_assert(!contiguous_vector<adapter_vector_type>);
		static_assert(!sized_vector<adapter_vector_type>);
		static_assert(!output_vector<adapter_vector_type>);
		static_assert(!static_extent_vector<adapter_vector_type>);
		static_assert(adapter_vector<adapter_vector_type>);
	}
	{
		using ss_binary_type = views::add_view<static_vector_type, static_vector_type>;

		static_assert(input_vector<ss_binary_type>);
		static_assert(!contiguous_vector<ss_binary_type>);
		static_assert(sized_vector<ss_binary_type>);
		static_assert(!output_vector<ss_binary_type>);
		static_assert(static_extent_vector<ss_binary_type>);

		using sd_binary_type = views::add_view<static_vector_type, dynamic_vector_type>;

		static_assert(input_vector<sd_binary_type>);
		static_assert(!contiguous_vector<sd_binary_type>);
		static_assert(sized_vector<sd_binary_type>);
		static_assert(!output_vector<sd_binary_type>);
		static_assert(static_extent_vector<sd_binary_type>);

		using sa_binary_type = views::add_view<static_vector_type, adapter_vector_type>;

		static_assert(input_vector<sa_binary_type>);
		static_assert(!contiguous_vector<sa_binary_type>);
		static_assert(sized_vector<sa_binary_type>);
		static_assert(!output_vector<sa_binary_type>);
		static_assert(static_extent_vector<sa_binary_type>);

		using da_binary_type = views::add_view<dynamic_vector_type, adapter_vector_type>;

		static_assert(input_vector<da_binary_type>);
		static_assert(!contiguous_vector<da_binary_type>);
		static_assert(sized_vector<da_binary_type>);
		static_assert(!output_vector<da_binary_type>);
		static_assert(!static_extent_vector<da_binary_type>);
	}

}