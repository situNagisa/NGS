#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/target.h"
#include "NGS/ngl/base/state.h"
#include "NGS/ngl/enum/framebuffer.h"
#include "NGS/ngl/framebuffer/attachment.h"

NGL_BEGIN
NGL_OBJ_BEGIN

class NGS_API FramebufferBase;

NGS_END
NGL_TARGET_BEGIN

class NGS_API Framebuffer final : public Target<Framebuffer, objects::FramebufferBase> {
	NGS_menvironment(Framebuffer);
private:
	friend base_type;
	static void _Select(state_type* state);
public:
	void SelectDefault(FramebufferTarget target = FramebufferTarget::framebuffer);
	bool CheckComplete(FramebufferTarget target = FramebufferTarget::framebuffer);
};

NGS_END
NGL_OBJ_BEGIN

class NGS_API FramebufferBase : public Object {
	NGS_menvironment(FramebufferBase);
public:
	static self_type& DEFAULT() {
		static FramebufferBase default_framebuffer;
		return default_framebuffer;
	}
protected:
	FramebufferBase()
		: target(ngl::FramebufferTarget::framebuffer)
	{}
public:
	explicit FramebufferBase(const FramebufferTarget target)
		: target(target)
	{
		NGL_CHECK(glGenFramebuffers(1, &_context));
	}
	FramebufferBase(self_type&& other) = default;

	virtual ~FramebufferBase()override {
		if (!_context)return;
		NGL_CHECK(glDeleteFramebuffers(1, &_context));
	}

	void Attach(Attachment attachment) {
		RequiredUpdate();
		_attachments.insert({ attachment.target,attachment });
	}
	void Attach(const FramebufferAttachment attachment, _Texture& texture, const int level = 0) {
		RequiredUpdate();
		Attach({ attachment,&texture });
	}
	void Attach(const FramebufferAttachment attachment, Renderbuffer& renderbuffer) {
		RequiredUpdate();
		Attach({ attachment,&renderbuffer });
	}

	const auto& GetAttachment(const FramebufferAttachment attachment)const {
		const auto it = _attachments.find(attachment);
		NGS_ASSERT(it != _attachments.end(), "not found attachment!");
		return it->second;
	}
	auto GetAttachment(const FramebufferAttachment attachment) {
		const auto it = _attachments.find(attachment);
		NGS_ASSERT(it != _attachments.end(), "not found attachment!");
		return it->second;
	}

	virtual void Update()override;
public:
	const FramebufferTarget target;
private:
	std::unordered_map<FramebufferAttachment, Attachment> _attachments{};
};

template<FramebufferTarget _Target>
struct Framebuffer : public FramebufferBase {
	NGS_menvironment(Framebuffer);
public:
	Framebuffer() : base_type(_Target) {}
	Framebuffer(self_type&& other) = default;
};

NGS_END

NGS_GL_GET_TARGET_FUNCTION(targets::Framebuffer, objects::FramebufferBase, framebuffer);

NGL_END
