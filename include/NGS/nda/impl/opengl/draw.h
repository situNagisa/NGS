#pragma once

#include "NGS/nda/impl/opengl/defined.h"
#include "NGS/nda/interfaces/interfaces.h"


NDA_IMPL_OPENGL_BEGIN

class NGS_API  Drawer : public IDrawer {
public:
	void Draw(const Stage* stage) override {
		boost::object_pool<matrix_t> transform_pool{ stage->GetNumChildrenRecurse() };
		_PrepareDisplayTransform(transform_pool, stage, mla::identity_matrix_v<3, float>());


	}
private:

	void _PrepareDisplayTransform(boost::object_pool<matrix_t>& pool, const DisplayObject* display, const matrix_t& parent_transform) {
		matrix_t& transform = *pool.malloc();
		display->user_data.other_data = &transform;

		transform = parent_transform * display->transform.GetMatrix();

		auto container = dynamic_cast<const DisplayObjectContainer*>(display);
		if (!container) return;
		for (size_t index = 0; index < container->GetNumChildren(); index++)
		{
			auto child = container->GetChild(index);
			_PrepareDisplayTransform(pool, child, transform);
		}
	}
private:

};

NDA_IMPL_OPENGL_END


