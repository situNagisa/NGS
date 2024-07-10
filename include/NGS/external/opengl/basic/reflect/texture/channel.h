#pragma once

#include "../../enum.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	NGS_DECLARE_TV_DEFAULT(texture_channel, enums::texture_channel_type, enums::texture_channel_type::none);
	NGS_DEFINE_TV(texture_channel, enums::texture_channel_type, ::std::int8_t, enums::texture_channel_type::integral_8);
	NGS_DEFINE_TV(texture_channel, enums::texture_channel_type, ::std::int16_t, enums::texture_channel_type::integral_16);
	NGS_DEFINE_TV(texture_channel, enums::texture_channel_type, ::std::int32_t, enums::texture_channel_type::integral_32);
	NGS_DEFINE_TV(texture_channel, enums::texture_channel_type, ::std::uint8_t, enums::texture_channel_type::unsigned_integral_8);
	NGS_DEFINE_TV(texture_channel, enums::texture_channel_type, ::std::uint16_t, enums::texture_channel_type::unsigned_integral_16);
	NGS_DEFINE_TV(texture_channel, enums::texture_channel_type, ::std::uint32_t, enums::texture_channel_type::unsigned_integral_32);
	NGS_DEFINE_TV(texture_channel, enums::texture_channel_type, float, enums::texture_channel_type::floating_point);
}

struct texture_channel_reflecter
{
	using type = enums::buffer_uniform_fundamental;

	template<class T>
	using reflect = ccpt::auto_constant<_detail::texture_channel_convert<type_traits::naked_t<T>>>;
};

using texture_channel_data = texture_channel_reflecter::type;

template<class T>
concept texture_channel = texture_channel_reflecter::reflect<T>::value != enums::texture_channel_type::none;

NGS_LIB_MODULE_END