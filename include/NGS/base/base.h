#pragma once
/*****************************************************************//**
 * \file   core.h
 * \brief
 *
 *	1:	version
 *	2:	STL	config
 *	3:	defined
 *	4:	type_trait library base_class
 *	5:	bit concepts
 *	6:	template_mate
 *
 * \author nagisa
 * \date   June 2023
 *********************************************************************/

#define NGS_USE_BASE 1

#include "NGS/base/basic.h"
#include "NGS/base/defined.h"

#include "NGS/base/type_info.h"
#include "NGS/base/utility.h"
#include "NGS/base/base_class.h"

#include "NGS/base/bit.h"
#include "NGS/base/concepts.h"

#include "NGS/base/log.h"
#include "NGS/base/assert.h"

#include "NGS/base/mpl/mpl.h"
#include "NGS/base/memory_reinterpreter.h"
