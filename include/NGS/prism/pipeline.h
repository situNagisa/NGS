#pragma once

#include "./description.h"
#include "./defined.h"

NGS_LIB_BEGIN

struct graphic_pipeline
{
	NGS_MPL_ENVIRON_BEGIN(graphic_pipeline);
public:
	graphic_pipeline(const NGS_PRISM_DESCRIPTION_NS::graphic_pipeline& info);
};

NGS_LIB_END