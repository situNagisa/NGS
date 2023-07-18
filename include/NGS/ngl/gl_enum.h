#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"

NGL_BEGIN

enum class BlendFactors : GLenum {
	zero = GL_ZERO,
	one = GL_ONE,
	src_color = GL_SRC_COLOR,
	one_minus_src_color = GL_ONE_MINUS_SRC_COLOR,
	dst_color = GL_DST_COLOR,
	one_minus_dst_color = GL_ONE_MINUS_DST_COLOR,
	src_alpha = GL_SRC_ALPHA,
	one_minus_src_alpha = GL_ONE_MINUS_SRC_ALPHA,
	dst_alpha = GL_DST_ALPHA,
	one_minus_dst_alpha = GL_ONE_MINUS_DST_ALPHA,
	constant_color = GL_CONSTANT_COLOR,
	one_minus_constant_color = GL_ONE_MINUS_CONSTANT_COLOR,
	constant_alpha = GL_CONSTANT_ALPHA,
	one_minus_constant_alpha = GL_ONE_MINUS_CONSTANT_ALPHA,
	src_alpha_saturate = GL_SRC_ALPHA_SATURATE,
};
enum class BlendEquations : GLenum {
	add = GL_FUNC_ADD,
	subtract = GL_FUNC_SUBTRACT,
	reverse_subtract = GL_FUNC_REVERSE_SUBTRACT,
	min = GL_MIN,
	max = GL_MAX,
};


enum class BufferTarget : GLenum {
	array = GL_ARRAY_BUFFER,
	atomic_counter = GL_ATOMIC_COUNTER_BUFFER,
	copy_read = GL_COPY_READ_BUFFER,
	copy_write = GL_COPY_WRITE_BUFFER,
	dispatch_indriect = GL_DISPATCH_INDIRECT_BUFFER,
	draw_indirect = GL_DRAW_INDIRECT_BUFFER,
	element = GL_ELEMENT_ARRAY_BUFFER,
	pixel_pack = GL_PIXEL_PACK_BUFFER,
	pixel_unpack = GL_PIXEL_UNPACK_BUFFER,
	query = GL_QUERY_BUFFER,
	shader_storage = GL_SHADER_STORAGE_BUFFER,
	texture = GL_TEXTURE_BUFFER,
	transform_feedback = GL_TRANSFORM_FEEDBACK_BUFFER,
	uniform = GL_UNIFORM_BUFFER,
};
enum class Usage : GLenum {
	stream_draw = GL_STREAM_DRAW,
	stream_read = GL_STREAM_READ,
	stream_copy = GL_STREAM_COPY,

	static_draw = GL_STATIC_DRAW,
	static_read = GL_STATIC_READ,
	static_copy = GL_STATIC_COPY,

	dynamic_draw = GL_DYNAMIC_DRAW,
	dynamic_read = GL_DYNAMIC_READ,
	dynamic_copy = GL_DYNAMIC_COPY,
};


enum class ErrorCode {
	no_error = GL_NO_ERROR,
	invalid_enum = GL_INVALID_ENUM,
	invalid_value = GL_INVALID_VALUE,
	invalid_operation = GL_INVALID_OPERATION,
	invalid_framebuffer_operation = GL_INVALID_FRAMEBUFFER_OPERATION,
	out_of_memory = GL_OUT_OF_MEMORY,
	stack_underflow = GL_STACK_UNDERFLOW,
	stack_overflow = GL_STACK_OVERFLOW,
};

enum class FramebufferStatus : GLenum {
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
enum class FramebufferAttachment : GLenum {
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

enum class FramebufferType : GLenum {
	framebuffer = GL_FRAMEBUFFER,
	read = GL_READ_FRAMEBUFFER,
	draw = GL_DRAW_FRAMEBUFFER,
};

enum class RenderbufferImageFormat {
	depth_component = GL_DEPTH_COMPONENT,
	depth_stencil = GL_DEPTH_STENCIL,
	stencil_index = GL_STENCIL_INDEX,
	R8 = GL_R8,
	RG8 = GL_RG8,
	RGB8 = GL_RGB8,
	RGBA8 = GL_RGBA8,
	R16F = GL_R16F,
	RG16F = GL_RG16F,
	RGB16F = GL_RGB16F,
	RGBA16F = GL_RGBA16F,
	R32F = GL_R32F,
	RG32F = GL_RG32F,
	RGB32F = GL_RGB32F,
	RGBA32F = GL_RGBA32F,
	R11FG11FB10F = GL_R11F_G11F_B10F,
	RGB9E5 = GL_RGB9_E5,
	R8I = GL_R8I,
	R8UI = GL_R8UI,
	R16I = GL_R16I,
	R16UI = GL_R16UI,
	R32I = GL_R32I,
	R32UI = GL_R32UI,
	RG8I = GL_RG8I,
	RG8UI = GL_RG8UI,
	RG16I = GL_RG16I,
	RG16UI = GL_RG16UI,
	RG32I = GL_RG32I,
	RG32UI = GL_RG32UI,
	RGB8I = GL_RGB8I,
	RGB8UI = GL_RGB8UI,
	RGB16I = GL_RGB16I,
	RGB16UI = GL_RGB16UI,
	RGB32I = GL_RGB32I,
	RGB32UI = GL_RGB32UI,
	RGBA8I = GL_RGBA8I,
	RGBA8UI = GL_RGBA8UI,
	RGBA16I = GL_RGBA16I,
	RGBA16UI = GL_RGBA16UI,
	RGBA32I = GL_RGBA32I,
	RGBA32UI = GL_RGBA32UI,
	depth_component16 = GL_DEPTH_COMPONENT16,
	depth_component24 = GL_DEPTH_COMPONENT24,
	depth_component32 = GL_DEPTH_COMPONENT32,
	depth_component32F = GL_DEPTH_COMPONENT32F,
	depth24_stencil = GL_DEPTH24_STENCIL8,
	depth32F_stencil8 = GL_DEPTH32F_STENCIL8,
};

enum class ShaderType {
	vertex = GL_VERTEX_SHADER,
	fragment = GL_FRAGMENT_SHADER,
	geometry = GL_GEOMETRY_SHADER,
	compute = GL_COMPUTE_SHADER,
	tess_control = GL_TESS_CONTROL_SHADER,
	tess_evaluation = GL_TESS_EVALUATION_SHADER,
};

enum class Capabilities {
	blend = GL_BLEND,
	clip_distance0 = GL_CLIP_DISTANCE0,
	clip_distance1 = GL_CLIP_DISTANCE1,
	clip_distance2 = GL_CLIP_DISTANCE2,
	clip_distance3 = GL_CLIP_DISTANCE3,
	clip_distance4 = GL_CLIP_DISTANCE4,
	clip_distance5 = GL_CLIP_DISTANCE5,
	clip_distance6 = GL_CLIP_DISTANCE6,
	clip_distance7 = GL_CLIP_DISTANCE7,
	color_logic_op = GL_COLOR_LOGIC_OP,
	cull_face = GL_CULL_FACE,
	debug_output = GL_DEBUG_OUTPUT,
	debug_output_synchronous = GL_DEBUG_OUTPUT_SYNCHRONOUS,
	depth_clamp = GL_DEPTH_CLAMP,
	depth_test = GL_DEPTH_TEST,
	dither = GL_DITHER,
	framebuffer_srgb = GL_FRAMEBUFFER_SRGB,
	line_smooth = GL_LINE_SMOOTH,
	multisample = GL_MULTISAMPLE,
	polygon_offset_fill = GL_POLYGON_OFFSET_FILL,
	polygon_offset_line = GL_POLYGON_OFFSET_LINE,
	polygon_offset_point = GL_POLYGON_OFFSET_POINT,
	polygon_smooth = GL_POLYGON_SMOOTH,
	primitive_restart = GL_PRIMITIVE_RESTART,
	primitive_restart_fixed_index = GL_PRIMITIVE_RESTART_FIXED_INDEX,
	rasterizer_discard = GL_RASTERIZER_DISCARD,
	sample_alpha_to_coverage = GL_SAMPLE_ALPHA_TO_COVERAGE,
	sample_alpha_to_one = GL_SAMPLE_ALPHA_TO_ONE,
	sample_coverage = GL_SAMPLE_COVERAGE,
	sample_shading = GL_SAMPLE_SHADING,
	sample_mask = GL_SAMPLE_MASK,
	scissor_test = GL_SCISSOR_TEST,
	stencil_test = GL_STENCIL_TEST,
	texture_cube_map_seamless = GL_TEXTURE_CUBE_MAP_SEAMLESS,
	program_point_size = GL_PROGRAM_POINT_SIZE,
};


enum class Wraps : GLint {
	repeat = GL_REPEAT,
	mirrored_repeat = GL_MIRRORED_REPEAT,
	clamp_to_edge = GL_CLAMP_TO_EDGE,
	clamp_to_border = GL_CLAMP_TO_BORDER,
};

enum class Filters : GLint {
	nearest = GL_NEAREST,
	linear = GL_LINEAR,
	nearest_mipmap_nearest = GL_NEAREST_MIPMAP_NEAREST,
	linear_mipmap_nearest = GL_LINEAR_MIPMAP_NEAREST,
	nearest_mipmap_linear = GL_NEAREST_MIPMAP_LINEAR,
	linear_mipmap_linear = GL_LINEAR_MIPMAP_LINEAR,
};

enum class TextureTarget : GLenum {
	_1D = GL_TEXTURE_1D,
	_2D = GL_TEXTURE_2D,
	_3D = GL_TEXTURE_3D,
	_1D_array = GL_TEXTURE_1D_ARRAY,
	_2D_array = GL_TEXTURE_2D_ARRAY,
	_rectangle = GL_TEXTURE_RECTANGLE,
};
enum class TextureSlot : GLenum {
	null = 0,
	_0 = GL_TEXTURE0,
	_1 = GL_TEXTURE1,
	_2 = GL_TEXTURE2,
	_3 = GL_TEXTURE3,
	_4 = GL_TEXTURE4,
	_5 = GL_TEXTURE5,
	_6 = GL_TEXTURE6,
	_7 = GL_TEXTURE7,
	_8 = GL_TEXTURE8,
	_9 = GL_TEXTURE9,
	_10 = GL_TEXTURE10,
	_11 = GL_TEXTURE11,
	_12 = GL_TEXTURE12,
	_13 = GL_TEXTURE13,
	_14 = GL_TEXTURE14,
	_15 = GL_TEXTURE15,
	_16 = GL_TEXTURE16,
	_17 = GL_TEXTURE17,
	_18 = GL_TEXTURE18,
	_19 = GL_TEXTURE19,
	_20 = GL_TEXTURE20,
	_21 = GL_TEXTURE21,
	_22 = GL_TEXTURE22,
	_23 = GL_TEXTURE23,
	_24 = GL_TEXTURE24,
	_25 = GL_TEXTURE25,
	_26 = GL_TEXTURE26,
	_27 = GL_TEXTURE27,
	_28 = GL_TEXTURE28,
	_29 = GL_TEXTURE29,
	_30 = GL_TEXTURE30,
	_31 = GL_TEXTURE31,
	end = _31 + 1,
	begin = _0,
};
inline TextureSlot operator+(TextureSlot slot, uint32 offset) { return (TextureSlot)((uint32)slot + offset); }
inline TextureSlot operator-(TextureSlot slot, uint32 offset) { return (TextureSlot)((uint32)slot - offset); }

enum class ElementDrawMode : GLenum {
	points = GL_POINTS,

	lines = GL_LINES,
	line_strip = GL_LINE_STRIP,
	line_loop = GL_LINE_LOOP,

	triangles = GL_TRIANGLES,
	triangle_strip = GL_TRIANGLE_STRIP,
	triangle_fan = GL_TRIANGLE_FAN,

	patches = GL_PATCHES,
};
enum class DrawMode : GLenum {
	points = GL_POINTS,

	lines = GL_LINES,
	line_strip = GL_LINE_STRIP,
	line_loop = GL_LINE_LOOP,

	line_strip_adjacency = GL_LINE_STRIP_ADJACENCY,
	lines_adjacency = GL_LINES_ADJACENCY,

	triangles = GL_TRIANGLES,
	triangle_strip = GL_TRIANGLE_STRIP,
	triangle_fan = GL_TRIANGLE_FAN,

	triangle_strip_adjacency = GL_TRIANGLE_STRIP_ADJACENCY,
	triangles_adjacency = GL_TRIANGLES_ADJACENCY,
};

NGL_END
