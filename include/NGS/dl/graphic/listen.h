#pragma once

#include "NGS/dl/defined.h"
#include "NGS/dl/display.h"

NGS_DL_BEGIN

class NGS_API Listen {
public:
	using display_object_constructor = void(*)(DisplayObject*);
	using display_object_destructor = void(*)(DisplayObject*);
	struct {
		display_object_constructor constructor = [](DisplayObject*) {};
		display_object_destructor destructor = [](DisplayObject*) {};
	}display_object{};

	using bitmap_data_constructor = void(*)(BitmapData*);
	using bitmap_data_destructor = void(*)(BitmapData*);
	using bitmap_data_copy = void(*)(BitmapData*,const BitmapData*);
	using bitmap_data_move = void(*)(BitmapData*, BitmapData*);
	struct {
		bitmap_data_constructor constructor = [](BitmapData*) {};
		bitmap_data_destructor destructor = [](BitmapData*) {};
		bitmap_data_copy copy = [](BitmapData*, const BitmapData*) {};
		bitmap_data_move move = [](BitmapData*, BitmapData*) {};
	}bitmap_data{};

	using graphic_create = std::unique_ptr<IGraphic>(*)();
	struct {
		graphic_create create = [] { return std::unique_ptr<IGraphic>(); };
	}graphic{};
};

NGS_DL_END
