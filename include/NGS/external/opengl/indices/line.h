#pragma once

#include "./point.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

inline constexpr struct
{
	template<::std::integral Index>
	constexpr decltype(auto) operator()(Index index, ::std::indirectly_writable<Index> auto out) const
		requires ::std::weakly_incrementable<Index>
	{
		add_point(index, out);
		++out;
		add_point(index + 1, out);
	}
	template<::std::integral Index>
	constexpr decltype(auto) operator()(Index index, ::std::size_t break_point_count, ::std::indirectly_writable<Index> auto out) const
		requires ::std::weakly_incrementable<Index>
	{
		for(auto i = index; i < index + break_point_count + 1; ++i)
		{
			(*this)(i, out);
			++out;
			++out;
		}
	}

	constexpr decltype(auto) operator()(::std::size_t break_point_count)const
	{
		return 2 * (break_point_count + 1);
	}
}add_line{};

NGS_LIB_MODULE_END