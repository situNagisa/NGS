#pragma once

#include "NGS/basic/basic.h"
#include "NGS/concepts/concepts.h"
#include "NGS/mpl/mpl.h"
#include "NGS/math/defined.h"

#define NGS_SPACE_BEGIN NGS_MATH_BEGIN namespace space {
#define NGS_SPACE_END } NGS_MATH_END

#define NGS_SPACE_SUPPORT_BEGIN NGS_SPACE_BEGIN inline namespace support{
#define NGS_SPACE_SUPPORT_END } NGS_SPACE_END

#define NGS_SPACE_ALIAS_3D(id,temp,_1,_2,_3) using id##_##_1##_##_2##_##_3 = temp<_1,_2,_3>

#define NGS_SPACE_ALIAS_3D_PERMUTATION(id,temp,_1,_2,_3)	\
NGS_SPACE_ALIAS_3D(id, temp, _1, _2, _3);					\
NGS_SPACE_ALIAS_3D(id, temp, _1, _3, _2);					\
NGS_SPACE_ALIAS_3D(id, temp, _2, _1, _3);					\
NGS_SPACE_ALIAS_3D(id, temp, _2, _3, _1);					\
NGS_SPACE_ALIAS_3D(id, temp, _3, _1, _2);					\
NGS_SPACE_ALIAS_3D(id, temp, _3, _2, _1)					\
//

#define NGS_SPACE_ALIAS_3D_ORTHOGRAPHIC(id,temp)	\
NGS_SPACE_ALIAS_3D_PERMUTATION(id, temp, x, y, z);	\
NGS_SPACE_ALIAS_3D_PERMUTATION(id, temp, x,my, z);	\
NGS_SPACE_ALIAS_3D_PERMUTATION(id, temp, x, y,mz);	\
NGS_SPACE_ALIAS_3D_PERMUTATION(id, temp, x,my,mz);	\
NGS_SPACE_ALIAS_3D_PERMUTATION(id, temp,mx, y, z);	\
NGS_SPACE_ALIAS_3D_PERMUTATION(id, temp,mx,my, z);	\
NGS_SPACE_ALIAS_3D_PERMUTATION(id, temp,mx, y,mz);	\
NGS_SPACE_ALIAS_3D_PERMUTATION(id, temp,mx,my,mz)	\
//