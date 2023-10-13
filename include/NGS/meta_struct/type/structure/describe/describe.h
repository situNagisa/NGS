#pragma once

#include "./concept.h"
#include "NGS/meta_struct/type/variable/traits.h"
#include "NGS/meta_struct/type/variable/dynamic_data.h"

NGS_META_STRUCT_TYPE_BEGIN

NGS_mfunction(struct_describe, class ...);

template<layout::CAlign _Align, CVariable... _Variable>
struct struct_describe<_Align, _Variable...> {
	using variable_types = mpl::vector<_Variable...>;

	// 第n个元变量
	template<size_t _Index> using variable_at = typename variable_types::template at_c<_Index>;

	// 元变量个数
	constexpr static size_t variable_count = variable_types::size;

	constexpr static size_t align = layout::align_as<_Align::value>(_Variable::align...);

	// 元结构体大小
	constexpr static size_t size = layout::size_of<align>(_Variable::size...);

	// 元变量对应的动态结构体数组（可动态访问
	NGS_mcst auto GET_VARIABLES() {
		constexpr std::array<size_t, variable_count> _counts = { variable_traits<_Variable>::element_count... };
		constexpr std::array<size_t, variable_count> _sizes = { _Variable::size... };
		constexpr std::array<size_t, variable_count> _offsets = layout::offset<align>(_Variable::size...);

		std::array<variable_d, variable_count> result{};
		for (size_t i = 0; i < variable_count; i++)
		{
			result[i].count = _counts[i];
			result[i].size = _sizes[i];
			result[i].offset = _offsets[i];
		}
		return result;
	}
};

NGS_META_STRUCT_TYPE_END
