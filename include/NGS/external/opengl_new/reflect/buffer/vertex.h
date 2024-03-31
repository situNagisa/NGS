#pragma once

#include "../../enum.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	NGS_DECLARE_TV_DEFAULT(buffer_vertex, enums::buffer_vertex_fundamental, enums::buffer_vertex_fundamental::none);
	NGS_DEFINE_TV(buffer_vertex, enums::buffer_vertex_fundamental, float32, enums::buffer_vertex_fundamental::floating_point_32);
	NGS_DEFINE_TV(buffer_vertex, enums::buffer_vertex_fundamental, float64, enums::buffer_vertex_fundamental::floating_point_64);
	NGS_DEFINE_TV(buffer_vertex, enums::buffer_vertex_fundamental, int8, enums::buffer_vertex_fundamental::integral_8);
	NGS_DEFINE_TV(buffer_vertex, enums::buffer_vertex_fundamental, int16, enums::buffer_vertex_fundamental::integral_16);
	NGS_DEFINE_TV(buffer_vertex, enums::buffer_vertex_fundamental, int32, enums::buffer_vertex_fundamental::integral_32);
	NGS_DEFINE_TV(buffer_vertex, enums::buffer_vertex_fundamental, uint8, enums::buffer_vertex_fundamental::unsigned_integral_8);
	NGS_DEFINE_TV(buffer_vertex, enums::buffer_vertex_fundamental, uint16, enums::buffer_vertex_fundamental::unsigned_integral_16);
	NGS_DEFINE_TV(buffer_vertex, enums::buffer_vertex_fundamental, uint32, enums::buffer_vertex_fundamental::unsigned_integral_32);

	//NGS_DEFINE_TV(buffer_vertex, fundamental_t, colors::primaries::RGBA24, GL_RGB);
	//NGS_DEFINE_TV(buffer_vertex, fundamental_t, colors::primaries::RGBA32, GL_RGBA);
}

struct buffer_vertex_reflecter
{
	struct type
	{
		enums::buffer_vertex_fundamental value;
		::std::size_t count;
	};

	template<class T>
	static constexpr auto _create()
	{
		using naked_type = type_traits::naked_t<T>;

		type result{enums::buffer_vertex_fundamental::none,1 };

		if constexpr (::std::is_bounded_array_v<T>)
		{
			result.value = _detail::buffer_vertex_convert<::std::ranges::range_value_t<naked_type>>;
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

using buffer_vertex_data = mpl::mstruct::basic::reflect_data<buffer_vertex_reflecter::type>;

template<class T>
concept buffer_vertex = buffer_vertex_reflecter::_create<T>().value != enums::buffer_vertex_fundamental::none;

NGS_LIB_MODULE_END