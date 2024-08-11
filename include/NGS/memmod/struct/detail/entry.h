#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace descriptors
{
	template<layouts::align_policy auto Policy, field_sequence FieldSequence>
	struct basic
	{
		constexpr static layouts::align_policy auto align_policy = Policy;
		using field_seq_type = FieldSequence;
	};

	template<layouts::align_policy auto Policy, fields::field... Fields>
	using descriptor = basic<Policy, ::std::tuple<Fields...>>;

	template<fields::field... Fields>
	using deduce = descriptor<layouts::policy::deduce(), Fields...>;

	template<::std::size_t Align, fields::field... Fields>
	using recommend = descriptor<layouts::policy::recommend(Align), Fields...>;

	template<::std::size_t Align, fields::field... Fields>
	using force = descriptor<layouts::policy::force(Align), Fields...>;

	template<fields::field... Fields>
	using no_align = force<1, Fields...>;
}

NGS_LIB_MODULE_END