#pragma once

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL.h"
#include "NGS/Embedded/Interface.h"

NGS_BEGIN

class Poll {
public:

	int operator()(int timeout);

private:
	ngs::void_ptr _data;
};

NGS_END
