﻿#pragma once

#include "NGS/ngl/environment/environment.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/error.h"

NGL_ENV_BEGIN

class BackgroundColor final : public IEnvironment {
public:
	void SetBackgroundColor(ARGB32 argb) { _background_color = argb; }
	auto GetBackgroundColor()const { return _background_color; }

	void Build() override {
		NGL_CHECK(glClearColor(
			ARGB32::R::Percent(_background_color.Red()),
			ARGB32::G::Percent(_background_color.Green()),
			ARGB32::B::Percent(_background_color.Blue()),
			ARGB32::A::Percent(_background_color.Alpha())
		));
	}

public:
	ARGB32 _background_color{};
};

NGL_ENV_END
