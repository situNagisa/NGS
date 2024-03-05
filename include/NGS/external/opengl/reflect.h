#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

namespace detail
{
	NGS_DECLARE_TV(gl, fundamental_t);
	NGS_DEFINE_TV(gl, fundamental_t, float32, GL_FLOAT);
	NGS_DEFINE_TV(gl, fundamental_t, float64, GL_DOUBLE);
	NGS_DEFINE_TV(gl, fundamental_t, int8, GL_BYTE);
	NGS_DEFINE_TV(gl, fundamental_t, uint8, GL_UNSIGNED_BYTE);
	NGS_DEFINE_TV(gl, fundamental_t, int16, GL_SHORT);
	NGS_DEFINE_TV(gl, fundamental_t, uint16, GL_UNSIGNED_SHORT);
	NGS_DEFINE_TV(gl, fundamental_t, int32, GL_INT);
	NGS_DEFINE_TV(gl, fundamental_t, uint32, GL_UNSIGNED_INT);

	NGS_DEFINE_TV(gl, fundamental_t, colors::primaries::RGBA24, GL_RGB);
	NGS_DEFINE_TV(gl, fundamental_t, colors::primaries::RGBA32, GL_RGBA);
}

struct reflecter
{
	struct type
	{
		fundamental_t value;
		::std::size_t count;
	};

	template<class T>
	static constexpr auto _create()
	{
		using naked_type = type_traits::naked_t<T>;

		type result{ 0,1 };

		if constexpr ( ::std::is_bounded_array_v<T> )
		{
			result.value = detail::gl_convert<::std::ranges::range_value_t<naked_type>>;
			result.count = ::std::extent_v<naked_type>;
		}
		else
		{
			result.value = detail::gl_convert<naked_type>;
		}

		//static_assert(result.value, "invalid type!");

		return result;
	}

	template<class T>
	using reflect = ccpt::auto_constant<_create<T>()>;
};

template<class T>
concept valid_fundamental = reflecter::_create<T>().value != 0;

using reflect_data = mpl::mstruct::basic::reflect_data<reflecter::type>;

NGS_LIB_END