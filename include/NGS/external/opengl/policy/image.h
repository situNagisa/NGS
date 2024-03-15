#pragma once

#include "../reflect.h"
#include "../context.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct image
{
	NGS_MPL_ENVIRON_BEGIN(image);
public:

	::std::size_t width;
	::std::size_t height;
	enums::internal_format internal_format;
	enums::format format;
	enums::channel_type channel_type;
	void_ptr_cst data;
};

template<valid_fundamental ChannelType, valid_fundamental Format, valid_fundamental InternalFormat = Format>
constexpr auto make_image(::std::size_t width, ::std::size_t height, const void_ptr_cst data)
{
	return image{
		.width = width,
		.height = height,
		.internal_format = static_cast<enums::internal_format>(reflecter::reflect<InternalFormat>::value.value),
		.format = static_cast<enums::format>(reflecter::reflect<Format>::value.value),
		.channel_type = static_cast<enums::channel_type>(reflecter::reflect<ChannelType>::value.value),
		.data = data
	};
}

NGS_LIB_MODULE_END
