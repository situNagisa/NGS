#pragma once

#include "NGS/concepts/any.h"

NGS_CCPT_BEGIN

/**
 * @brief  CRPT 子类应满足概念`_DerivedConcept`
*/
template<class  T = void, bool _DerivedConcept = false>
concept CRPT = true;

NGS_CCPT_END

