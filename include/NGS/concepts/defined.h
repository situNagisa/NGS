#pragma once

#include "NGS/base/base.h"

#define NGS_CCPT_BEGIN NGS_BEGIN namespace ccpt{
#define NGS_CCPT_END } NGS_END

#define NGS_CCPT_VERIFY(cpt,...) static_assert(cpt<__VA_ARGS__>,"the class " #__VA_ARGS__ " does not satisfy the concept " #cpt);
#define NGS_CCPT_VERIFY2(...) static_assert(__VA_ARGS__);
