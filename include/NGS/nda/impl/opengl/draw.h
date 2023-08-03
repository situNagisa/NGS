#pragma once

#include "NGS/nda/impl/opengl/defined.h"
#include "NGS/nda/interfaces/interfaces.h"


NDA_IMPL_OPENGL_BEGIN

class Drawer : public IDrawer{
public:
	void Draw(const Stage* stage) override;

private:
	void _DrawTarget(const DisplayObject* target);
};

NDA_IMPL_OPENGL_END


