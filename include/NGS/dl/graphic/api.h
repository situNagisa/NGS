#pragma once

#include "NGS/dl/graphic/listen.h"

NGS_DL_BEGIN

class NGS_API GraphicAPI : public Singleton<GraphicAPI> {
private:
	using base_type = GraphicAPI::self_type;
	friend base_type;
	GraphicAPI() = default;
public:

	Listen listener;
};

NGS_DL_END
