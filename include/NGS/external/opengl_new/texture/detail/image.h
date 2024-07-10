#pragma once

#include "./reflect.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct image
{
	NGS_PP_INJECT_BEGIN(image);
public:

	::std::size_t width;
	::std::size_t height;
	enums::texture_internal_format internal_format;
	enums::texture_format format;
	enums::texture_channel_type channel_type;
	const void* data;
};

template<texture_channel ChannelType>
constexpr auto make_image(::std::size_t width, ::std::size_t height, const void* data, enums::texture_internal_format internal_format, enums::texture_format format)
{
	return image{
		.width = width,
		.height = height,
		.internal_format = internal_format,
		.format = format,
		.channel_type = channel_reflecter::reflect<ChannelType>::value,
		.data = data
	};
}

template<texture_channel ChannelType>
constexpr decltype(auto) make_image(::std::size_t width, ::std::size_t height, const void* data, enums::texture_format format)
{
	return NGS_LIB_MODULE_NAME::make_image<ChannelType>(width, height, data, static_cast<enums::texture_internal_format>(format), format);
}

NGS_LIB_MODULE_END
