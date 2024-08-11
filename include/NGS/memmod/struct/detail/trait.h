#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

NGS_TCEA_TRAIT_DEFAULT_TYPE(field_seq, void);
NGS_TCEA_TRAIT_ALIAS_T(field_seq);
NGS_TCEA_TRAIT_HAS_TYPE_OBJECT(field_seq, field_seq_type);

NGS_TCEA_TRAIT_DEFAULT_VALUE(align_policy, layouts::policy::deduce());
NGS_TCEA_TRAIT_ALIAS_V(align_policy);
NGS_TCEA_TRAIT_HAS_VALUE_OBJECT(align_policy, align_policy);

NGS_LIB_MODULE_END