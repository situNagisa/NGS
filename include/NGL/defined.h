#pragma once

#include "NGS/base/base.h"
#include "NGS/extend/extend.h"
#include "NGS/math/math.h"

#define NGL_BEGIN NGS_BEGIN namespace ngl{
#define NGL_END } NGS_END

NGL_BEGIN

template<class T>
concept Context = requires(T t, const T t_cst) {
	bool(t_cst);
}
&& std::equality_comparable<T>
;

template<class _Manager, class _Context>
concept ContextManager = requires() {
	{ _Manager::GetContext() } -> std::convertible_to<_Context>;
	{ _Manager::SetContext(_Context{}) } -> std::same_as<void>;
};

NGL_END

namespace ngl = ::ngs::ngl;