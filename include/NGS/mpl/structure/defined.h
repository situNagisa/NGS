#pragma once

#include "NGS/boost/fusion.h"
#include "NGS/boost/stl_interfaces.h"

#include "NGS/basic/basic.h"
#include "NGS/ccpt/ccpt.h"
#include "NGS/layout/layout.h"
#include "NGS/mpl/defined.h"
#include "NGS/static/string.h"


#define NGS_STRUCTURE_BEGIN NGS_MPL_BEGIN namespace mstruct{
#define NGS_STRUCTURE_END } NGS_MPL_END

#define NGS_STRUCTURE_TYPE_BEGIN NGS_STRUCTURE_BEGIN inline namespace type{
#define NGS_STRUCTURE_TYPE_END } NGS_STRUCTURE_END

#define NGS_STRUCTURE_CONTAINER_BEGIN NGS_STRUCTURE_BEGIN namespace container{
#define NGS_STRUCTURE_CONTAINER_END } NGS_STRUCTURE_END
