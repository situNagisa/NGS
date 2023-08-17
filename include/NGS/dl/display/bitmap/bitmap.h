#pragma once

#include "NGS/dl/defined.h"
#include "NGS/dl/display/display.h"
#include "NGS/dl/display/bitmap/idata.h"

NGS_DL_BEGIN

class NGS_API Bitmap : public DisplayObject {
public:
	using base_type = DisplayObject;

	using base_type::base_type;
	Bitmap()
		: base_type("bitmap")
	{}

	explicit Bitmap(IBitmapData* bitmap_data)
		: _bitmap_data(bitmap_data)
	{}

	virtual ~Bitmap()override = default;

	void SetBitmapData(IBitmapData* bitmap_data){ _bitmap_data = bitmap_data;}
	IBitmapData* GetBitmapData(){ return _bitmap_data;}
	const IBitmapData* GetBitmapData()const { return _bitmap_data;}
private:
	IBitmapData* _bitmap_data = nullptr;
};

NGS_DL_END
