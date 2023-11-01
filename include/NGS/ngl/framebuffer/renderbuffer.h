#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/target.h"
#include "NGS/ngl/base/object.h"
#include "NGS/ngl/enum/image_format.h"
#include "NGS/ngl/error.h"

NGL_BEGIN
NGL_OBJ_BEGIN

class NGS_DLL_API Renderbuffer;

NGS_END
NGL_TARGET_BEGIN

class NGS_DLL_API Renderbuffer final : public Target<Renderbuffer, objects::Renderbuffer> {
	NGS_MPL_ENVIRON(Renderbuffer);
private:
	friend base_type;
	static void _Select(state_type* state);
};

NGS_END

NGS_GL_GET_TARGET_FUNCTION(targets::Renderbuffer, objects::Renderbuffer, renderbuffer);

NGL_OBJ_BEGIN

class NGS_DLL_API Renderbuffer final : public Object {
	NGS_MPL_ENVIRON(Renderbuffer);
public:
	Renderbuffer(size_t width, size_t height, RenderbufferImageFormat format)
		: _format(format)
		, _size(width, height)
	{
		NGL_CHECK(glGenRenderbuffers(1, &_context));
	}
	Renderbuffer(size_t width, size_t height)
		: Renderbuffer(width, height, RenderbufferImageFormat::depth24_stencil8)
	{}

	virtual ~Renderbuffer() override {
		NGL_CHECK(glDeleteRenderbuffers(1, &_context));
	}

	virtual void Update() override;

	void SetStorage(size_t width, size_t height) { SetStorage(width, height, _format); }
	void SetStorage(size_t width, size_t height, RenderbufferImageFormat format) {
		RequiredUpdate();
		_format = format;
		_size.Set(width, height);
	}
public:
	const GLenum target = GL_RENDERBUFFER;
private:
	RenderbufferImageFormat _format = RenderbufferImageFormat::depth24_stencil8;
	Point2s _size;
};

NGS_END
NGL_END
