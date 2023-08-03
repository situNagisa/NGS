#pragma once

#include "NGS/nda/defined.h"
#include "NGS/nda/display/display.h"
#include "NGS/nda/display/bitmap/idata.h"
#include "NGS/nda/display/bitmap/data.h"
#include "NGS/nda/display/bitmap/data_view.h"

NDA_BEGIN

class Bitmap : public DisplayObject {
public:
	using DisplayObject::DisplayObject;
	virtual ~Bitmap()override {}

	IBitmapData* bitmap_data = nullptr;

	virtual std::string ToString()const override { return name.empty() ? "bitmap" : name; }
};

NDA_END
