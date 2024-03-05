#pragma once

#include "./point.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

inline constexpr struct
{
	template<::std::integral Index>
	constexpr decltype(auto) operator()(Index index, ::std::size_t triangle_count, ::std::indirectly_writable<Index> auto out) const
		requires ::std::weakly_incrementable<decltype(out)>
	{
		using index_type = type_traits::naked_t<Index>;
		for (index_type i = static_cast<index_type>(0); i < triangle_count; ++i)
		{
			add_point(index, out);
			++out;
			add_point(index + i + 1, out);
			++out;
			add_point(index + i + 2, out);
			++out;
		}
	}
	constexpr decltype(auto) operator()(::std::size_t triangle_count)const
	{
		return 3 * triangle_count;
	}
}add_polygon{};

NGS_LIB_MODULE_END