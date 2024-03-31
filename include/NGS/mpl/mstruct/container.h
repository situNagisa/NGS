#pragma once

#include "./container/variable.h"
#include "./container/fields.h"
#include "./container/struct.h"
#include "./container/storage.h"
#include "./container/named.h"
#include "./container/named_pair.h"

NGS_LIB_MODULE_EXPORT(meta_variable);
NGS_LIB_MODULE_EXPORT(meta_struct);
NGS_LIB_MODULE_EXPORT(storage);
NGS_LIB_MODULE_EXPORT(named_struct);
NGS_LIB_MODULE_EXPORT(named_pair);

#include "NGS/lib/module_end.h"
