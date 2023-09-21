#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/enum/framebuffer.h"
#include "NGS/ngl/texture/texture.h"
#include "NGS/ngl/framebuffer/renderbuffer.h"

NGL_BEGIN

class NGS_API Attachment {
protected:
	using self_type = Attachment;
public:
	Attachment(FramebufferAttachment target)
		: target(target)
	{}
	Attachment(FramebufferAttachment target,objects::_Texture* texture)
		: target(target)
	{
		SetTexture(texture);
	}
	Attachment(FramebufferAttachment target, objects::Renderbuffer* renderbuffer)
		: target(target)
	{
		SetRenderbuffer(renderbuffer);
	}

	bool Empty()const { return _tag == null; }
	bool IsTexture()const { return _tag == texture; }
	bool IsRenderbuffer()const { return _tag == renderbuffer; }

	void SetTexture(objects::_Texture* texture) {
		_tag = self_type::texture;
		_attachment._texture = texture;
	}
	void SetRenderbuffer(objects::Renderbuffer* renderbuffer) {
		_tag = self_type::renderbuffer;
		_attachment._renderbuffer = renderbuffer;
	}
	void SetNull() { _tag = self_type::null; }

	void Update() {
		switch (_tag)
		{
		case ngs::ngl::Attachment::null:
			break;
		case ngs::ngl::Attachment::texture:
			_attachment._texture->Update();
			break;
		case ngs::ngl::Attachment::renderbuffer:
			_attachment._renderbuffer->Update();
			break;
		default:
			break;
		}
	}

	objects::_Texture* GetTexture()const { return _attachment._texture; }
	objects::Renderbuffer* GetRenderbuffer()const { return _attachment._renderbuffer; }
public:
	const FramebufferAttachment target;
private:
	enum { null, texture, renderbuffer } _tag = null;
	union {
		objects::_Texture* _texture = nullptr;
		objects::Renderbuffer* _renderbuffer;
	} _attachment;
};

NGL_END
