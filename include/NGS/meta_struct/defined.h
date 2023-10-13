#pragma once

#include "NGS/basic/basic.h"
#include "NGS/concepts/concepts.h"
#include "NGS/mpl/mpl.h"
#include "NGS/layout/layout.h"

#define NGS_META_STRUCT_BEGIN NGS_BEGIN namespace meta_struct{
#define NGS_META_STRUCT_END } NGS_END

#define NGS_META_STRUCT_TYPE_BEGIN NGS_META_STRUCT_BEGIN inline namespace type{
#define NGS_META_STRUCT_TYPE_END } NGS_META_STRUCT_END

#define NGS_META_STRUCT_CONTAINER_BEGIN NGS_META_STRUCT_BEGIN namespace container{
#define NGS_META_STRUCT_CONTAINER_END } NGS_META_STRUCT_END
