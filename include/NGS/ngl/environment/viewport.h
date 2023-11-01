#pragma once

#include "NGS/ngl/environment/environment.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/error.h"

NGL_ENV_BEGIN

class NGS_DLL_API Viewport final : public IEnvironment {
public:

	void Build() override {
		NGL_CHECK(glViewport(range.x, range.y, range.width, range.height));
	}

	Rectanglei range{};
public:
};

NGL_ENV_END
