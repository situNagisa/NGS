#pragma once

#include "../../enum.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	NGS_DECLARE_TV_DEFAULT(buffer_indices, enums::buffer_indices_fundamental, enums::buffer_indices_fundamental::none);
	NGS_DEFINE_TV(buffer_indices, enums::buffer_indices_fundamental, uint8, enums::buffer_indices_fundamental::unsigned_integral_8);
	NGS_DEFINE_TV(buffer_indices, enums::buffer_indices_fundamental, uint16, enums::buffer_indices_fundamental::unsigned_integral_16);
	NGS_DEFINE_TV(buffer_indices, enums::buffer_indices_fundamental, uint32, enums::buffer_indices_fundamental::unsigned_integral_32);
}

struct buffer_indices_reflecter
{
	using type = enums::buffer_indices_fundamental;

	template<class T>
	using reflect = ccpt::auto_constant<_detail::buffer_indices_convert<type_traits::naked_t<T>>>;
};

using buffer_indices_data = mpl::mstruct::basic::reflect_data<buffer_indices_reflecter::type>;

template<class T>
concept buffer_indices = buffer_indices_reflecter::reflect<T>::value != enums::buffer_indices_fundamental::none;

NGS_LIB_MODULE_END