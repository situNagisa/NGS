#pragma once

#include "NGS/dl/display/get_display_stage.h"

NGS_DL_BEGIN 

NGS_HPP_INLINE Stage* get_display_stage(DisplayObject* display) {
	DisplayObjectContainer* container = display->GetParent();
	do {
		if (!container->GetParent())break;
		container = container->GetParent();
	} while (container);
	return as<Stage>(container);
}

NGS_HPP_INLINE const Stage* get_display_stage(const DisplayObject* display) {
	const DisplayObjectContainer* container = display->GetParent();
	do {
		if (!container->GetParent())break;
		container = container->GetParent();
	} while (container);
	return as<Stage>(container);
}

NGS_DL_END