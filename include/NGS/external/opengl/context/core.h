#pragma once

#include "./detail.h"
#include "./defined.h"

NGS_LIB_BEGIN

using details::context_t;
using details::context;
using details::context_machine;
using details::raii_context;
using details::null_context;

using details::state_machine;
using details::state_machine_t;
using details::machine;

using details::bind;
using details::bindable;
#if defined(NGS_EXTERNAL_OPENGL_CONTEXT_CHECK_BIND)
using details::is_binding;
using details::unbind;
#endif

NGS_LIB_END