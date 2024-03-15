#pragma once

#include "../enum.h"
#include "../basic.h"
#include "../context.h"
#include "../algorithm.h"
#include "./image.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<enums::texture_target Target>
struct basic_texture
{
	NGS_MPL_ENVIRON_BEGIN(basic_texture);
public:
	using context_type = contexts::basic_texture<Target>;

	explicit(false) basic_texture(const image& image, ::std::size_t mipmap_level = 0)
	{
		basic::bind(_context);
		algorithm::texture_set_image(_context,image.data, image.width, image.height,image.internal_format,image.format,image.channel_type, mipmap_level);
		generate_mipmap();
	}

	void set_wrap_s(enums::wraps wrap) { algorithm::texture_set_wrap_s(_context, wrap); }
	void set_wrap_t(enums::wraps wrap) { algorithm::texture_set_wrap_t(_context, wrap); }
	void set_wrap_r(enums::wraps wrap) { algorithm::texture_set_wrap_r(_context, wrap); }

	void set_minify_filter(enums::filters filter) { algorithm::texture_set_minify_filter(_context, filter); }
	void set_magnify_filter(enums::filters filter) { algorithm::texture_set_magnify_filter(_context, filter); }

	void generate_mipmap() { algorithm::texture_generate_mipmap(_context); }

	constexpr auto&& get_context()const { return _context; }

	context_type _context;
};

using texture_1d = basic_texture<enums::texture_target::_1d>;
using texture_1d_array = basic_texture<enums::texture_target::_1d_array>;
using texture_2d = basic_texture<enums::texture_target::_2d>;
using texture_2d_array = basic_texture<enums::texture_target::_2d_array>;
using texture_3d = basic_texture<enums::texture_target::_3d>;
using texture_rectangle = basic_texture<enums::texture_target::rectangle>;

NGS_LIB_MODULE_END