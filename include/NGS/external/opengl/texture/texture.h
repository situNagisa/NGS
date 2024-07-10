#pragma once

#include "../basic.h"
#include "./image.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_target Target>
struct basic_texture
{
	NGS_PP_INJECT_BEGIN(basic_texture);
public:
	using context_type = NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::basic_texture<Target>;

	explicit(false) basic_texture(const image& image, ::std::size_t mipmap_level = 0)
	{
		NGS_EXTERNAL_OPENGL_BASIC_CONTEXT_NS::bind(_context);
		_context.set_image(image.data, image.width, image.height,image.internal_format,image.format,image.channel_type, mipmap_level);
		generate_mipmap();
	}

	void set_wrap_s(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::wraps wrap) { _context.set_wrap_s(wrap); }
	void set_wrap_t(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::wraps wrap) { _context.set_wrap_t(wrap); }
	void set_wrap_r(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::wraps wrap) { _context.set_wrap_r(wrap); }

	void set_minify_filter(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::filters filter) { _context.set_minify_filter(filter); }
	void set_magnify_filter(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::filters filter) { _context.set_magnify_filter(filter); }

	void generate_mipmap() { _context.generate_mipmap(); }

	constexpr auto&& get_context()const { return _context; }

	context_type _context;
};

using texture_1d = basic_texture<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_target::_1d>;
using texture_1d_array = basic_texture<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_target::_1d_array>;
using texture_2d = basic_texture<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_target::_2d>;
using texture_2d_array = basic_texture<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_target::_2d_array>;
using texture_3d = basic_texture<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_target::_3d>;
using texture_rectangle = basic_texture<NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::texture_target::rectangle>;

NGS_LIB_MODULE_END