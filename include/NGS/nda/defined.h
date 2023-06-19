#pragma once

#include "NGS/nda/depend.h"
#include "NGS/nda/config.h"

#define NDA_BEGIN NGS_BEGIN namespace nda{
#define NDA_END } NGS_END

NDA_BEGIN

NGS_TYPE_DEFINE(NDA_NUMBER_TYPE, number);
NGS_TYPE_DEFINE(Rectangle<__number>, rect);
NGS_TYPE_DEFINE(Point2_<__number>, point);
NGS_TYPE_DEFINE(Matrix<__number>, matrix);
NGS_TYPE_DEFINE(Transform<__number>, transform);

NGS_TYPE_DEFINE(NDA_COLOR_TYPE, color);

template<class _Derived, class _Base>
	requires std::derived_from<_Derived, _Base>
_Derived* down_cast(_Base* base) { return dynamic_cast<_Derived*>(base); }
template<class _Derived, class _Base>
	requires std::derived_from<_Derived, _Base>
const _Derived* down_cast(const _Base* base) { return dynamic_cast<const _Derived*>(base); }

NDA_END

namespace nda = ::ngs::nda;