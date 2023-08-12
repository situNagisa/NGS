#pragma once

#include "NGS/nda/defined.h"
#include "NGS/nda/display/display.h"
#include "NGS/nda/display/sprite.h"

NDA_BEGIN

class Stage : public Sprite, public DeleteCopy {
public:
	using Sprite::Sprite;

	virtual std::string ToString()const override { return Format("%s:[%d]", name.empty() ? "stage" : name.c_str(), GetNumChildren()); }
};

inline Stage* get_display_stage(DisplayObject* display) {
	DisplayObjectContainer* container = display->GetParent();
	do {
		if (!container->GetParent())break;
		container = container->GetParent();
	} while (container);
	return dynamic_cast<Stage*>(container);
}
inline const Stage* get_display_stage(const DisplayObject* display) {
	const DisplayObjectContainer* container = display->GetParent();
	do {
		if (!container->GetParent())break;
		container = container->GetParent();
	} while (container);
	return dynamic_cast<const Stage*>(container);
}

NDA_END
