#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/enum/blend.h"
#include "NGS/ngl/enum/buffer.h"
#include "NGS/ngl/enum/capabilities.h"
#include "NGS/ngl/enum/draw.h"
#include "NGS/ngl/enum/error_code.h"
#include "NGS/ngl/enum/filters.h"
#include "NGS/ngl/enum/image_format.h"
#include "NGS/ngl/enum/shader.h"
#include "NGS/ngl/enum/texture.h"
#include "NGS/ngl/enum/usage.h"
#include "NGS/ngl/enum/wraps.h"
#include "NGS/ngl/enum/cursor.h"

NGL_BEGIN

enum class  FramebufferStatus : GLenum {
	complete = GL_FRAMEBUFFER_COMPLETE,
	undefined = GL_FRAMEBUFFER_UNDEFINED,
	incomplete_attachment = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
	incomplete_missing_attachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
	incomplete_draw_buffer = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
	incomplete_read_buffer = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
	unsupported = GL_FRAMEBUFFER_UNSUPPORTED,
	incomplete_multisample = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
	incomplete_layer_targets = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS,
};
enum class  FramebufferAttachment : GLenum {
	color0 = GL_COLOR_ATTACHMENT0,
	color1 = GL_COLOR_ATTACHMENT1,
	color2 = GL_COLOR_ATTACHMENT2,
	color3 = GL_COLOR_ATTACHMENT3,
	color4 = GL_COLOR_ATTACHMENT4,
	color5 = GL_COLOR_ATTACHMENT5,
	color6 = GL_COLOR_ATTACHMENT6,
	color7 = GL_COLOR_ATTACHMENT7,
	color8 = GL_COLOR_ATTACHMENT8,
	color9 = GL_COLOR_ATTACHMENT9,
	color10 = GL_COLOR_ATTACHMENT10,
	color11 = GL_COLOR_ATTACHMENT11,
	color12 = GL_COLOR_ATTACHMENT12,
	color13 = GL_COLOR_ATTACHMENT13,
	color14 = GL_COLOR_ATTACHMENT14,
	color15 = GL_COLOR_ATTACHMENT15,
	depth = GL_DEPTH_ATTACHMENT,
	stencil = GL_STENCIL_ATTACHMENT,
	depth_stencil = GL_DEPTH_STENCIL_ATTACHMENT,
};

enum class  FramebufferType : GLenum {
	framebuffer = GL_FRAMEBUFFER,
	read = GL_READ_FRAMEBUFFER,
	draw = GL_DRAW_FRAMEBUFFER,
};

NGL_END
