#pragma once

#include "NGS/ngl/environment/environment.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/error.h"

NGL_ENV_BEGIN

class NGS_API  Capabilities final : public IEnvironment {
public:
	void Enable(Capability c) { _capabilities.insert(c); }
	void Disable(Capability c) { _capabilities.erase(c); }
	bool IsEnabled(Capability c)const { return _capabilities.find(c) != _capabilities.end(); }

	void Build() override {
		for (auto c : _capabilities) {
			NGL_CHECK(glEnable(static_cast<GLenum>(c)));
		}
	}
	void Destroy() override {
		for (auto c : _capabilities) {
			NGL_CHECK(glDisable(static_cast<GLenum>(c)));
		}
	}

private:
	std::unordered_set<Capability> _capabilities{};
};

NGL_ENV_END
