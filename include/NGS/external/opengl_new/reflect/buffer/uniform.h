#pragma once

#include "../../enum.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	NGS_DECLARE_TV_DEFAULT(buffer_uniform, enums::buffer_uniform_fundamental, enums::buffer_uniform_fundamental::none);
	NGS_DEFINE_TV(buffer_uniform, enums::buffer_uniform_fundamental, int32, enums::buffer_uniform_fundamental::integral);
	NGS_DEFINE_TV(buffer_uniform, enums::buffer_uniform_fundamental, uint32, enums::buffer_uniform_fundamental::unsigned_integral);
	NGS_DEFINE_TV(buffer_uniform, enums::buffer_uniform_fundamental, float, enums::buffer_uniform_fundamental::floating_point);
}

struct buffer_uniform_reflecter
{
	struct type
	{
		enums::buffer_uniform_fundamental value;
		::std::size_t dimension;
		::std::size_t count;
	};

	template<class T>
	static constexpr auto _create()
	{
		using naked_type = type_traits::naked_t<T>;

		type result{ enums::buffer_uniform_fundamental::none,1, 1 };

		if constexpr (::std::is_bounded_array_v<T>)
		{
			result.value = _detail::buffer_vertex_convert<type_traits::naked_t<::std::ranges::range_value_t<naked_type>>>;
			result.count = ::std::extent_v<naked_type>;
		}
		else
		{
			result.value = _detail::buffer_vertex_convert<naked_type>;
		}

		//static_assert(result.value, "invalid type!");

		return result;
	}

	template<class T>
	using reflect = ccpt::auto_constant<_create<T>()>;
};

using buffer_uniform_data = buffer_uniform_reflecter::type;

template<class T>
concept buffer_uniform = buffer_uniform_reflecter::reflect<T>::value != enums::buffer_uniform_fundamental::none;

NGS_LIB_MODULE_END