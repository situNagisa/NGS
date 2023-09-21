#pragma once

#include "NGS/ngl/environment/environment.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/error.h"

NGL_ENV_BEGIN

class NGS_API  BackgroundColor final : public IEnvironment {
public:
	void SetBackgroundColor(ARGB32 argb) { _background_color = argb; }
	auto GetBackgroundColor()const { return _background_color; }

	void Build() override {
		NGL_CHECK(glClearColor(
			ARGB32::R::PERCENT(_background_color.Red()),
			ARGB32::G::PERCENT(_background_color.Green()),
			ARGB32::B::PERCENT(_background_color.Blue()),
			ARGB32::A::PERCENT(_background_color.Alpha())
		));
	}

public:
	ARGB32 _background_color{};
};

NGL_ENV_END
