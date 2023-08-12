#pragma once

#include "NGS/ngl/defined.h"

#define NGL_ENV_BEGIN NGL_BEGIN namespace env {
#define NGL_ENV_END } NGL_END

NGL_ENV_BEGIN

class IEnvironment {
public:
	virtual void Build() {};
	virtual void Destroy() {};
};

NGL_ENV_END
