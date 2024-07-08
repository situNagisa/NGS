#pragma once

#include "../description.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _T>
concept graphic_pipeline =
::std::constructible_from<_T, const descriptions::graphic_pipeline&>&&
	requires(_T t)
{

};
NGS_PRISM_INTERFACE_DELEGATE(graphic_pipeline, graphic_pipeline);


NGS_LIB_MODULE_END