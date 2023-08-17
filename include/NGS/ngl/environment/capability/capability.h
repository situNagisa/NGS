#pragma once

#include "NGS/ngl/environment/environment.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/error.h"

NGL_ENV_BEGIN

struct NGS_API ICapability : public IEnvironment {
public:
	virtual Capability GetDependCapability()const = 0;
};

NGL_ENV_END
