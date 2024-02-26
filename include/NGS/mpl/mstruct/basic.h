#pragma once

#include "./basic/field_count.h"
#include "./basic/fields.h"
#include "./basic/field_at.h"
#include "./basic/align.h"
#include "./basic/size.h"
#include "./basic/reflect.h"
#include "./basic/concept.h"
#include "./basic/field_data.h"
#include "./basic/meta.h"
#include "./basic/field_offset.h"

NGS_LIB_BEGIN

template<class T>
inline constexpr NGS_LIB_MODULE_NAME::reflect_functor<T> reflect{};

NGS_LIB_END

#include "NGS/lib/module_end.h"