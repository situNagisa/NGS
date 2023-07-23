#include "defined.h"

TEST(nda, display) {
	nda::Sprite stage("stage");

	auto& l0 = *new nda::Sprite("l0");
	auto& l1 = *new nda::Sprite("l1");
	auto& container = *new nda::Sprite("container");
	auto& b0 = *new nda::Bitmap("b0");
	auto& b1 = *new nda::Bitmap("b1");
	auto& l2 = *new nda::Sprite("l2");

	stage.AddChild(l0);
	stage.AddChild(l1);
	l1.AddChild(container);
	container.AddChild(b0);
	container.AddChild(b1);
	stage.AddChild(l2);

	NGS_LOGL(debug, "\n", stage.GetTreeStruct());

	EXPECT_EQ(stage.GetNumChildren(), 3);
	EXPECT_EQ(l1.GetNumChildren(), 1);
	EXPECT_EQ(container.GetNumChildren(), 2);
	EXPECT_EQ(l2.GetNumChildren(), 0);
}
