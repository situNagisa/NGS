#pragma once

#include "NGS/base/base.h"

NGS_BEGIN

struct NGS_DLL_API UserData {
	void_ptr user_data = nullptr;
	void_ptr other_data = nullptr;
};

NGS_END
