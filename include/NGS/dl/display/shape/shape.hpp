#pragma once

#include "NGS/dl/display/shape/shape.h"
#include "NGS/dl/graphic/api.h"

NGS_DL_BEGIN

NGS_HPP_INLINE Shape::Shape()
	: graphic(GraphicAPI::I().listener.graphic.create())
{
}

NGS_DL_END
