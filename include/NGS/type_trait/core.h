#pragma once

#include "./detail.h"
#include "./defined.h"

NGS_LIB_BEGIN

using details::naked_t;
using details::object_t;

using details::index_type_identity;
using details::index_type_identity_t;

using details::add_const_like_t;
using details::add_volatile_like_t;
using details::add_reference_like_t;
using details::add_pointer_like_t;
using details::add_cv_like_t;
using details::add_cvref_like_t;

NGS_LIB_END