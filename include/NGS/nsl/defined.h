#pragma once

#include "NGS/extend/extend.h"
#include "NGS/math/math.h"
#include "NGS/embedded/embedded.h"

#define NSL_BEGIN NGS_BEGIN namespace nsl{
#define NSL_END } NGS_END

NSL_BEGIN

class NSLObject {

};

class NSLDevice : public EmbeddedObject, public NSLObject {

};

NSL_END

namespace nsl = ::ngs::nsl;