#pragma once

#include "NGS/basic/basic.h"
#include "NGS/concepts/concepts.h"
#include "NGS/mpl/mpl.h"

#define NGS_COORDINATE_BEGIN NGS_BEGIN namespace coordinates {
#define NGS_COORDINATE_END } NGS_END

#define NGS_COORDINATE_SUPPORT_BEGIN NGS_COORDINATE_BEGIN inline namespace support{
#define NGS_COORDINATE_SUPPORT_END } NGS_COORDINATE_END

#define NGS_COORDINATE_ALIAS_3D(id,temp,_1,_2,_3) using id##_##_1##_##_2##_##_3 = temp<_1,_2,_3>

#define NGS_COORDINATE_ALIAS_3D_PERMUTATION(id,temp,_1,_2,_3)	\
NGS_COORDINATE_ALIAS_3D(id, temp, _1, _2, _3);					\
NGS_COORDINATE_ALIAS_3D(id, temp, _1, _3, _2);					\
NGS_COORDINATE_ALIAS_3D(id, temp, _2, _1, _3);					\
NGS_COORDINATE_ALIAS_3D(id, temp, _2, _3, _1);					\
NGS_COORDINATE_ALIAS_3D(id, temp, _3, _1, _2);					\
NGS_COORDINATE_ALIAS_3D(id, temp, _3, _2, _1)					\
//

#define NGS_COORDINATE_ALIAS_3D_ORTHOGRAPHIC(id,temp)	\
NGS_COORDINATE_ALIAS_3D_PERMUTATION(id, temp, x, y, z);	\
NGS_COORDINATE_ALIAS_3D_PERMUTATION(id, temp, x,my, z);	\
NGS_COORDINATE_ALIAS_3D_PERMUTATION(id, temp, x, y,mz);	\
NGS_COORDINATE_ALIAS_3D_PERMUTATION(id, temp, x,my,mz);	\
NGS_COORDINATE_ALIAS_3D_PERMUTATION(id, temp,mx, y, z);	\
NGS_COORDINATE_ALIAS_3D_PERMUTATION(id, temp,mx,my, z);	\
NGS_COORDINATE_ALIAS_3D_PERMUTATION(id, temp,mx, y,mz);	\
NGS_COORDINATE_ALIAS_3D_PERMUTATION(id, temp,mx,my,mz)	\
//