#pragma once

#include "./context.h"
#include "./image.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<enums::texture_target Target>
decltype(auto) make_texture(const image& image, ::std::size_t mipmap_level = 0)
{
	basic_texture<Target> result{};
	contextes::bind(result);
	result.set_image(image.data, image.width, image.height, image.internal_format, image.format, image.channel_type, mipmap_level);
	result.generate_mipmap();
	return result;
}


using texture_1d = basic_texture<enums::texture_target::_1d>;
using texture_1d_array = basic_texture<enums::texture_target::_1d_array>;
using texture_2d = basic_texture<enums::texture_target::_2d>;
using texture_2d_array = basic_texture<enums::texture_target::_2d_array>;
using texture_3d = basic_texture<enums::texture_target::_3d>;
using texture_rectangle = basic_texture<enums::texture_target::rectangle>;

NGS_LIB_MODULE_END