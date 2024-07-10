#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace reflects
{
	NGS_TVM_TV_REGISTER_DEFAULT(texture_channel, enums::texture_channel_type, enums::texture_channel_type::none);
	NGS_TVM_TV_INSERT(texture_channel, ::std::int8_t, enums::texture_channel_type::integral_8);
	NGS_TVM_TV_INSERT(texture_channel, ::std::int16_t, enums::texture_channel_type::integral_16);
	NGS_TVM_TV_INSERT(texture_channel, ::std::int32_t, enums::texture_channel_type::integral_32);
	NGS_TVM_TV_INSERT(texture_channel, ::std::uint8_t, enums::texture_channel_type::unsigned_integral_8);
	NGS_TVM_TV_INSERT(texture_channel, ::std::uint16_t, enums::texture_channel_type::unsigned_integral_16);
	NGS_TVM_TV_INSERT(texture_channel, ::std::uint32_t, enums::texture_channel_type::unsigned_integral_32);
	NGS_TVM_TV_INSERT(texture_channel, float, enums::texture_channel_type::floating_point);
}

struct channel_reflecter
{
	using type = enums::buffer_uniform_fundamental;

	template<class T>
	using reflect = ccpt::auto_constant<reflects::texture_channel::value<type_traits::naked_t<T>>>;
};

using channel_data = channel_reflecter::type;

template<class T>
concept texture_channel = channel_reflecter::reflect<T>::value != enums::texture_channel_type::none;

NGS_LIB_MODULE_END