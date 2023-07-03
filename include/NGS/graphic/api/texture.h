#pragma once

#include "NGS/extend/extend.h"
#include "NGS/graphic/api/image.h"

NGS_BEGIN

template<class T>
concept CTexture = requires(T t, const T t_cst) {
	//{ *t_cst.GetImage() } -> CImage;
	{ t_cst.GetWidth() } -> std::convertible_to<size_t>;
	{ t_cst.GetHeight() } -> std::convertible_to<size_t>;
	{ t.SetWidth(0) };
	{ t.SetHeight(0) };
};

NGS_END
