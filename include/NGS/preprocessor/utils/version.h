#pragma once

#include "./to_string.h"

#define NGS_PP_VERSION(major, minor, patch) ((major) * 10000 + (minor) * 100 + (patch))
#define NGS_PP_VERSION_MAJOR(version) ((version) / 10000)
#define NGS_PP_VERSION_MINOR(version) (((version) / 100) % 100)
#define NGS_PP_VERSION_PATCH(version) ((version) % 100)