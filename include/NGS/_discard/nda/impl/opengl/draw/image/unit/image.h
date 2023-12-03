#pragma once

#include "NGS/nda/impl/opengl/draw/base/unit.h"

NDA_IMPL_OPENGL_BEGIN

struct NGS_DLL_API ImageDrawUnit : IDrawUnit {
	using base_type = IDrawUnit;

	ImageDrawUnit(Bitmap* bitmap)
		: base_type(bitmap)
	{
		if (!bitmap->bitmap_data)return;
		ngl::ImageView image(std::launder(reinterpret_cast<const RGBA32*>(bitmap->bitmap_data->GetData())), bitmap->bitmap_data->GetWidth(), bitmap->bitmap_data->GetHeight());
		NGS_NEW(texture, ngl::objects::Texture2D)(image);
	}
	~ImageDrawUnit() {
		if (texture) {
			NGS_DELETE(texture);
		}
	}

	virtual void Render()override {
		base_type::Render();
	}

	Bitmap* GetBitmap() { return static_cast<Bitmap*>(display); }

	ngl::objects::Texture2D* texture = nullptr;
};

NDA_IMPL_OPENGL_END
