#pragma once

#include "NGS/nda/defined.h"

NDA_BEGIN

class NGS_DLL_API  IBitmapData {
public:

	virtual byte_ptr_cst GetData()const = 0;
	virtual size_t GetSize()const = 0;

	template<CColor _Color>
	const _Color* GetData()const { return std::launder(reinterpret_cast<const _Color*>(GetData())); }

	virtual color_space::PixelFormat GetFormat()const = 0;

	virtual size_t GetWidth()const = 0;
	virtual size_t GetHeight()const = 0;
};

NDA_END
