#pragma once

#include "NGS/ngl/environment/environment.h"
#include "NGS/ngl/shader/shader.h"

NGL_ENV_BEGIN

class NGS_API  Shader final : public IEnvironment {
public:
	Shader() = default;
	Shader(const std::shared_ptr<objects::Shader>& shader) :_shader(shader) {}

	void SetShader(const std::shared_ptr<objects::Shader>& shader) { _shader = shader; }
	auto& GetShader() { return _shader; }
	const auto& GetShader()const { return _shader; }

	virtual void Build() override {
		_shader->Update();
		if (!is_bind(*_shader))
			bind(*_shader);
	}

public:
	std::shared_ptr<objects::Shader> _shader = nullptr;
};

NGL_ENV_END
