#pragma once

#include "NGS/ngl/environment/environment.h"
#include "NGS/ngl/framebuffer/framebuffer.h"

NGL_ENV_BEGIN

class NGS_DLL_API Framebuffer final : public IEnvironment {
public:
	Framebuffer() = default;
	Framebuffer(const std::shared_ptr<objects::FramebufferBase>& framebuffer) : _framebuffer(framebuffer) {}
	Framebuffer(const FramebufferTarget target)
		: _framebuffer(std::make_shared<objects::FramebufferBase>(target))
	{}

	void SetFramebuffer(const std::shared_ptr<objects::FramebufferBase>& framebuffer) { _framebuffer = framebuffer; }
	auto& SetFramebuffer() { return _framebuffer; }
	const auto& GetFramebuffer()const { return _framebuffer; }

	virtual void Build() override {
		_framebuffer->Update();
		bind(*_framebuffer);
	}
	virtual void Destroy() override {
		OpenGL::I().framebuffer->SelectDefault(_framebuffer->target);
	}

public:
	std::shared_ptr<objects::FramebufferBase> _framebuffer = nullptr;
};

NGL_ENV_END
