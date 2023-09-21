#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/base/state.h"

NGL_BEGIN
NGL_OBJ_BEGIN


class NGS_API  Object : public State {
	NGS_menvironment(Object);
public:
	using State::State;
	Object(Object&&) = default;
	virtual ~Object() = default;
};

NGS_END
NGL_END
