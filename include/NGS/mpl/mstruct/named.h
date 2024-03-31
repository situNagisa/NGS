#pragma once

#include "./named/concept.h"
#include "./named/field.h"
#include "./named/named_fields.h"
#include "./named/field_at.h"
#include "./named/get.h"

NGS_LIB_MODULE_EXPORT(named_structure);
NGS_LIB_MODULE_EXPORT(named_field);
NGS_LIB_MODULE_EXPORT(named_fields);
NGS_LIB_MODULE_EXPORT(name);
NGS_LIB_MODULE_EXPORT(named_pair_name_t);
NGS_LIB_MODULE_EXPORT(named_pair_field_t);
NGS_LIB_MODULE_EXPORT(named_field_at_t);
NGS_LIB_MODULE_EXPORT(get);
NGS_LIB_MODULE_EXPORT(struct_named_fields_t);

#include "NGS/lib/module_end.h"