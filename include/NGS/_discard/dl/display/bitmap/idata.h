#pragma once

#include "NGS/dl/defined.h"

NGS_DL_BEGIN

class NGS_DLL_API IBitmapData{
public:
	virtual ~IBitmapData() = default;

	/**
	 * \brief 获取底层数据
	 * 
	 * \return 指向底层数据的指针
	 */
	virtual byte_ptr_cst GetData()const = 0;
	template<CColor _ColorType> const _ColorType* GetData()const{ return std::launder(reinterpret_cast<const _ColorType*>(GetData())); }

	virtual size_t GetWidth()const = 0;
	virtual size_t GetHeight()const = 0;

	virtual color_space::PixelFormat GetFormat()const = 0;
};

NGS_DL_END
