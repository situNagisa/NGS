#pragma once

#include "NGS/ngl/environment/environment.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/error.h"

NGL_ENV_BEGIN

class Clear final : public IEnvironment {
public:
	void SetClearBitfield(GLbitfield bitfield) { _clear_bitfield = bitfield; }
	auto GetClearBitfield()const { return _clear_bitfield; }

	void Build() override {
		NGL_CHECK(glClear(_clear_bitfield));
	}

public:
	GLbitfield _clear_bitfield = 0;
};

NGL_ENV_END
