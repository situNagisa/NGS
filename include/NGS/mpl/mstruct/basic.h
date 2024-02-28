#pragma once

#include "./basic/field_count.h"
#include "./basic/fields.h"
#include "./basic/field_at.h"
#include "./basic/align.h"
#include "./basic/size.h"
#include "./basic/reflect.h"
#include "./basic/concept.h"
#include "./basic/field_data.h"
#include "./basic/field_offset.h"

NGS_LIB_BEGIN

template<class T, NGS_LIB_MODULE_NAME::reflecter Reflecter = NGS_LIB_MODULE_NAME::zero_reflecter>
inline constexpr NGS_LIB_MODULE_NAME::reflect_functor<T, Reflecter> reflect{};

NGS_LIB_END

NGS_LIB_MODULE_EXPORT(structure);
NGS_LIB_MODULE_EXPORT(field_count_v);
NGS_LIB_MODULE_EXPORT(fields_t);
NGS_LIB_MODULE_EXPORT(field_at_t);
NGS_LIB_MODULE_EXPORT(struct_align_v);
NGS_LIB_MODULE_EXPORT(struct_size_v);
NGS_LIB_MODULE_EXPORT(field_data);
NGS_LIB_MODULE_EXPORT(field_offset_v);

#include "NGS/lib/module_end.h"