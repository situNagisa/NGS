#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct image
{
	NGS_PP_INJECT_BEGIN(image);
public:

	::std::size_t width;
	::std::size_t height;
	NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_internal_format internal_format;
	NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_format format;
	NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_channel_type channel_type;
	void_ptr_cst data;
};

template<basic::reflects::texture_channel ChannelType>
constexpr auto make_image(::std::size_t width, ::std::size_t height, const void_ptr_cst data, NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_internal_format internal_format, NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_format format)
{
	return image{
		.width = width,
		.height = height,
		.internal_format = internal_format,
		.format = format,
		.channel_type = NGS_EXTERNAL_OPENGL_BASIC_REFLECT_NS::texture_channel_reflecter::reflect<ChannelType>::value,
		.data = data
	};
}

template<basic::reflects::texture_channel ChannelType>
constexpr decltype(auto) make_image(::std::size_t width, ::std::size_t height, const void_ptr_cst data, NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_format format)
{
	return NGS_LIB_MODULE_NAME::make_image<ChannelType>(width, height, data, static_cast<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_internal_format>(format), format);
}

NGS_LIB_MODULE_END
