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
	using type = enums::buffer_uniform_fundamental;

	template<class T>
	using reflect = ccpt::auto_constant<_detail::buffer_uniform_convert<type_traits::naked_t<T>>>;
};

using buffer_uniform_data = buffer_uniform_reflecter::type;

template<class T>
concept buffer_uniform = buffer_uniform_reflecter::reflect<T>::value != enums::buffer_uniform_fundamental::none;

NGS_LIB_MODULE_END